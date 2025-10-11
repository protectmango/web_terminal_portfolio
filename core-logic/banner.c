// core-logic/banner.c
// This program prints the initial welcome message and core command list upon terminal launch.

#include <stdio.h>
#include <stdlib.h>

// ANSI Escape Codes for formatting (Must match the codes used in help.c and main.js)
#define ANSI_COLOR_YELLOW   "\x1b[1;33m" // Bold Yellow (Header/Prompt)
#define ANSI_COLOR_GREEN    "\x1b[0;32m" // Green (General text)
#define ANSI_COLOR_CYAN     "\x1b[1;36m" // Bold Cyan (Commands)
#define ANSI_COLOR_RESET    "\x1b[0m"    // Reset all formatting

int main() {
    // --- SSH-Style Welcome Banner ---
    printf("\n");
    printf(ANSI_COLOR_YELLOW "======================================================================\n" ANSI_COLOR_RESET);
     // --- Core Commands List (Simplified) ---
    printf(ANSI_COLOR_YELLOW "  Initial Available Commands:\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_CYAN "  ---------------------------------------------------\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_CYAN "  > help      : " ANSI_COLOR_GREEN "Display the FULL list of all available commands.\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_CYAN "  > skills    : " ANSI_COLOR_GREEN "Show core technical expertise (C, Networking, Embedded).\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_CYAN "  > projects  : " ANSI_COLOR_GREEN "Display a showcase of key C/Embedded projects.\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_CYAN "  > resume    : " ANSI_COLOR_GREEN "Download my professional CV.\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_CYAN "  ---------------------------------------------------\n" ANSI_COLOR_RESET);

    printf("\n" ANSI_COLOR_GREEN "  Type 'help' for the complete list of Networking and Utility commands.\n\n" ANSI_COLOR_RESET);

    return 0;
}
