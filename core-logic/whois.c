// core-logic/whois.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

#define WHOIS_SERVER "whois.internic.net"
#define WHOIS_PORT 43
#define BUFFER_SIZE 4096
#define ANSI_COLOR_RED "\x1b[1;31m"
#define ANSI_COLOR_CYAN "\x1b[1;36m"
#define ANSI_COLOR_RESET "\x1b[0m"

// Function to print error messages to stderr, which the Node.js server captures.
void error_exit(const char *msg) {
    fprintf(stderr, ANSI_COLOR_RED "Error: %s\n" ANSI_COLOR_RESET, msg);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
    int sockfd, bytes_received, total_bytes = 0;
    struct sockaddr_in server_addr;
    struct hostent *server;
    char buffer[BUFFER_SIZE];
    char *query_domain;
    char query[256];

    // 1. Argument Validation
    if (argc != 2) {
        fprintf(stdout, ANSI_COLOR_RED "Usage:\n" ANSI_COLOR_RESET);
        fprintf(stdout, "  whois <domain_name>\n");
        fprintf(stdout, ANSI_COLOR_CYAN "Example: whois google.com\n" ANSI_COLOR_RESET);
        return 0; // Return 0 (success) to print usage to stdout
    }
    
    query_domain = argv[1];
    
    // 2. Resolve Hostname (DNS Lookup)
    printf(ANSI_COLOR_CYAN "Querying WHOIS for %s...\n" ANSI_COLOR_RESET, query_domain);
    printf("Connecting to %s on Port %d...\n", WHOIS_SERVER, WHOIS_PORT);
    
    server = gethostbyname(WHOIS_SERVER);
    if (server == NULL) {
        error_exit("DNS resolution failed for WHOIS server.");
    }

    // 3. Create Socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        error_exit("Could not create socket.");
    }

    // 4. Set up Server Address Structure
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    // Copy the resolved IP address into the structure
    memcpy(&server_addr.sin_addr.s_addr, server->h_addr_list[0], server->h_length);
    server_addr.sin_port = htons(WHOIS_PORT);

    // 5. Connect to Server
    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        error_exit("Connection failed (Server refused or timeout).");
    }

    // 6. Send WHOIS Query
    // WHOIS protocol requires the query followed by CRLF (\r\n)
    snprintf(query, sizeof(query), "%s\r\n", query_domain);
    
    if (send(sockfd, query, strlen(query), 0) < 0) {
        error_exit("Failed to send query.");
    }
    
    printf("\n" ANSI_COLOR_CYAN "--- WHOIS RESPONSE ---" ANSI_COLOR_RESET "\n");

    // 7. Receive and Print Response
    while ((bytes_received = recv(sockfd, buffer, BUFFER_SIZE - 1, 0)) > 0) {
        // Null-terminate the received data chunk
        buffer[bytes_received] = '\0'; 
        // Print the data chunk to standard output (captured by Node.js)
        printf("%s", buffer);
        total_bytes += bytes_received;
    }

    if (bytes_received < 0) {
        error_exit("Receive failed.");
    }
    
    // 8. Cleanup
    close(sockfd);

    printf(ANSI_COLOR_CYAN "\n--- %d Bytes Received ---\n" ANSI_COLOR_RESET, total_bytes);
    
    return 0;
}
