// core-logic/help.c
#include <stdio.h>

#define ANSI_COLOR_YELLOW   "\x1b[1;33m"
#define ANSI_COLOR_CYAN     "\x1b[1;36m"
#define ANSI_COLOR_RESET    "\x1b[0m"

int main() {
    printf(ANSI_COLOR_YELLOW "\nAvailable Commands:\n" ANSI_COLOR_RESET);
    printf("-----------------------------------\n");
    
    printf(ANSI_COLOR_CYAN "%-15s" ANSI_COLOR_RESET "Display a list of all commands.\n", "help");
    printf(ANSI_COLOR_CYAN "%-15s" ANSI_COLOR_RESET "Show my core technical skills.\n", "skills");
    printf(ANSI_COLOR_CYAN "%-15s" ANSI_COLOR_RESET "Display a list of key C/Embedded projects.\n", "projects");
    printf(ANSI_COLOR_CYAN "%-15s" ANSI_COLOR_RESET "Display my resume (Embedded Trainee Engineer).\n", "resume");
    printf(ANSI_COLOR_CYAN "%-15s" ANSI_COLOR_RESET "Here I have written a simple about me.\n", "about");

    printf(ANSI_COLOR_YELLOW "\nNetworking & Systems:\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_CYAN "%-15s" ANSI_COLOR_RESET "Query WHOIS information for a domain (e.g., whois google.com).\n", "whois");
    printf(ANSI_COLOR_CYAN "%-15s" ANSI_COLOR_RESET "Perform a custom UDP DNS A-record lookup (e.g., dns_resolve example.com).\n", "dns_resolve");
    printf(ANSI_COLOR_CYAN "%-15s" ANSI_COLOR_RESET "Simulate active network connections and states.\n", "netstat");
    
    printf(ANSI_COLOR_YELLOW "\nTerminal Utility:\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_CYAN "%-15s" ANSI_COLOR_RESET "Clear the terminal screen.\n", "clear");
    printf("-----------------------------------\n\n");
    
    return 0;
}
