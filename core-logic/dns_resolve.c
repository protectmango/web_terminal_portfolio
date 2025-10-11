// core-logic/dns_resolve.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define DNS_SERVER "8.8.8.8" // Google's Public DNS
#define DNS_PORT 53
#define BUFFER_SIZE 512

// --- DNS Protocol Structures ---

// 1. DNS Header (12 bytes)
struct DNS_HEADER {
    unsigned short id; // identification number
    
    unsigned char rd : 1; // recursion desired
    unsigned char tc : 1; // truncated message
    unsigned char aa : 1; // authoritive answer
    unsigned char opcode : 4; // purpose of message
    unsigned char qr : 1; // query/response flag
    
    unsigned char rcode : 4; // response code
    unsigned char cd : 1; // checking disabled
    unsigned char ad : 1; // authenticated data
    unsigned char z : 1; // must be zero
    unsigned char ra : 1; // recursion available
    
    unsigned short q_count; // number of question entries
    unsigned short ans_count; // number of answer entries
    unsigned short auth_count; // number of authority entries
    unsigned short add_count; // number of resource entries
};

// 2. Question structure (QTYPE and QCLASS)
struct QUESTION {
    unsigned short qtype;
    unsigned short qclass;
};

// 3. Pointers to question name and question structure in the message
struct QUERY {
    unsigned char *name;
    struct QUESTION *ques;
};

// --- Helper Functions ---

// Converts "www.google.com" to "3www6google3com0" (DNS QNAME format)
void change_to_dns_format(unsigned char* dns, const char* host) {
    // The fix: Change 'int lock = 0;' to 'size_t lock = 0;'
    size_t lock = 0;
    
    // We must use a mutable copy of the string to append '.'
    char temp_host[256];
    // Use strncpy for safety
    strncpy(temp_host, host, sizeof(temp_host) - 1);
    temp_host[sizeof(temp_host) - 1] = '\0'; // Ensure null termination
    strcat(temp_host, ".");

    // Use size_t for both counters to eliminate signed/unsigned warnings
    for(size_t i = 0; i < strlen(temp_host); i++) {
        if(temp_host[i] == '.') {
            // Since 'i' and 'lock' are both size_t, the subtraction result
            // 'i - lock' is also safe to cast to unsigned char for the label length.
            *dns++ = i - lock; 
            
            // Inner loop now uses size_t comparison: 'lock < i' is clean.
            for(; lock < i; lock++) { 
                *dns++ = temp_host[lock];
            }
            lock++; 
        }
    }
    *dns++ = 0;
}

// Custom error function
void error_exit(const char *msg) {
    fprintf(stderr, "\x1b[1;31mError: %s\x1b[0m\n", msg);
    exit(EXIT_FAILURE);
}

// --- Main Program ---
int main(int argc, char *argv[]) {
    int sockfd;
    struct sockaddr_in dest_addr;
    unsigned char buf[BUFFER_SIZE], *qname, *reader;
    struct DNS_HEADER *dns = NULL;
    struct sockaddr_in a;
    
    if (argc != 2) {
        printf("\x1b[1;31mUsage:\n\x1b[0m  dns_resolve <hostname>\n");
        printf("\x1b[1;36mExample: dns_resolve example.com\x1b[0m\n");
        return 0; 
    }

    const char *hostname = argv[1];

    // 1. Setup UDP Socket
    sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sockfd < 0) error_exit("Failed to create socket.");

    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(DNS_PORT);
    // Convert server IP string to network address structure
    if (inet_aton(DNS_SERVER, &dest_addr.sin_addr) == 0) error_exit("Invalid DNS server IP.");

    // 2. Construct DNS Query Packet
    
    // Set DNS Header fields
    dns = (struct DNS_HEADER *) &buf;
    dns->id = (unsigned short) htons(getpid()); // Unique ID
    dns->qr = 0;      // This is a query
    dns->opcode = 0;  // Standard query
    dns->aa = 0;      // Not authoritative
    dns->tc = 0;      // Not truncated
    dns->rd = 1;      // Recursion desired
    dns->ra = 0;      // Recursion available (will be set in response)
    dns->z = 0;
    dns->ad = 0;
    dns->cd = 0;
    dns->rcode = 0;
    dns->q_count = htons(1); // We have 1 question
    dns->ans_count = 0;
    dns->auth_count = 0;
    dns->add_count = 0;

    // Set Question Name (QNAME)
    qname = (unsigned char*)&buf[sizeof(struct DNS_HEADER)];
    change_to_dns_format(qname, hostname);

    // Set Question Type (A Record) and Class (IN - Internet)
    struct QUESTION *qinfo = (struct QUESTION*) &buf[sizeof(struct DNS_HEADER) + (strlen((const char*)qname) + 1)];
    qinfo->qtype = htons(1); // Type A (Host Address)
    qinfo->qclass = htons(1); // Class IN (Internet)
    
    int query_size = sizeof(struct DNS_HEADER) + (strlen((const char*)qname) + 1) + sizeof(struct QUESTION);

    // 3. Send Query
    printf("\x1b[1;36m-> Resolving %s via UDP...\n\x1b[0m", hostname);
    if (sendto(sockfd, buf, query_size, 0, (struct sockaddr*)&dest_addr, sizeof(dest_addr)) < 0) {
        error_exit("Failed to send DNS query.");
    }

    // 4. Receive Response
    socklen_t addr_len = sizeof(dest_addr);
    int response_size = recvfrom(sockfd, buf, BUFFER_SIZE, 0, (struct sockaddr*)&dest_addr, &addr_len);
    if (response_size < 0) {
        error_exit("Failed to receive DNS response.");
    }
    
    // 5. Parse Response (Focus on A record)
    dns = (struct DNS_HEADER*) buf;
    
    // Move reader past Header and Question
    reader = &buf[query_size]; 
    
    if (ntohs(dns->ans_count) > 0) {
        printf("\n\x1b[1;33m--- DNS Resolution Result ---\x1b[0m\n");
        printf("Answer Count: %d\n", ntohs(dns->ans_count));
        
        // Skip Name (2 bytes for pointer compression) and QTYPE/QCLASS fields of the first answer
        // Note: For simplicity, we assume no CNAME redirection and go straight to the A record.
        reader += 2 + 4 + 4 + 2; // Pointer, Type (2), Class (2), TTL (4), Data Length (2)
        
        // Read the 4-byte RDATA (the IP address)
        unsigned int *p_ip = (unsigned int*)reader;
        a.sin_addr.s_addr = (*p_ip);
        
        // Output the result
        printf("\x1b[0;32mIP Address:\x1b[0m %s\n", inet_ntoa(a.sin_addr));
        printf("----------------------------------\n");
    } else {
        printf("\x1b[1;31mResolution Failed.\x1b[0m No answer records found.\n");
        if (dns->rcode != 0) printf("Response Code: %d (Error)\n", dns->rcode);
    }
    
    close(sockfd);
    
    return 0;
}
