// core-logic/netstat.c
#include <stdio.h>
#include <string.h>

// ANSI Escape Codes for formatting
#define ANSI_COLOR_CYAN     "\x1b[1;36m" // Bold Cyan (Header)
#define ANSI_COLOR_GREEN    "\x1b[0;32m" // Green (Status)
#define ANSI_COLOR_YELLOW   "\x1b[0;33m" // Yellow (LISTEN)
#define ANSI_COLOR_RESET    "\x1b[0m"    // Reset all formatting

// --- FIX 1: INCREASE SIZE OF 'State' FIELD ---
// The escape codes (e.g., "\x1b[0;33m") take about 7-8 bytes. 
// Original size was 16. New size of 32 is safe for "ESTABLISHED" + two full color codes.
typedef struct {
    char Proto[8];
    char LocalAddress[32];
    char ForeignAddress[32];
    char State[32]; // Increased size from 16 to 32
    char PID[16];
} Connection;

// Array of simulated connections
Connection connections[] = {
    {"tcp", "127.0.0.1:3000", "0.0.0.0:*", ANSI_COLOR_YELLOW "LISTEN" ANSI_COLOR_RESET, "1234/node"},
    {"tcp", "10.0.0.5:41234", "142.250.72.3:443", ANSI_COLOR_GREEN "ESTABLISHED" ANSI_COLOR_RESET, "5678/chrome"},
    {"tcp", "10.0.0.5:56789", "18.172.100.2:22", "TIME_WAIT", "4321/ssh"},
    {"udp", "0.0.0.0:53", "0.0.0.0:*", "", "9876/dnsmasq"}, 
    {"tcp", "127.0.0.1:8080", "127.0.0.1:54321", "CLOSE_WAIT", "1122/nginx"},
    {"tcp", "0.0.0.0:22", "0.0.0.0:*", ANSI_COLOR_YELLOW "LISTEN" ANSI_COLOR_RESET, "3344/sshd"},
};

int main() {
    int num_connections = sizeof(connections) / sizeof(connections[0]);

    printf(ANSI_COLOR_CYAN "\n--- Active Network Connections (Simulated netstat) ---\n" ANSI_COLOR_RESET);
    
    // Print Header
    printf("%-5s %-20s %-20s %-15s %-15s\n", 
           "Proto", "Local Address", "Foreign Address", "State", "PID/Program");
    
    // Print Separator
    printf("----- -------------------- -------------------- --------------- ---------------\n");

    // Print Connection Data
    for (int i = 0; i < num_connections; i++) {
        // --- FIX 2: SIMPLIFY PRINTF ---
        // We use %s for all fields. The ANSI codes are invisible to padding calculation,
        // so we just rely on the fixed width of 15 characters, which is sufficient for a terminal demo.
        printf("%-5s %-20s %-20s %-15s %-15s\n", 
               connections[i].Proto,
               connections[i].LocalAddress,
               connections[i].ForeignAddress,
               connections[i].State, // Prints the string containing ANSI codes
               connections[i].PID
        );
    }

    printf("\n\x1b[0;34mNote: This command simulates low-level network states using C for demonstration purposes.\n" ANSI_COLOR_RESET);

    return 0;
}
