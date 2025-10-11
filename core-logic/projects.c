// core-logic/projects.c
#include <stdio.h>

// ANSI Escape Codes for formatting
#define ANSI_COLOR_YELLOW   "\x1b[1;33m" // Bold Yellow (Header)
#define ANSI_COLOR_GREEN    "\x1b[0;32m" // Green (Project Title)
#define ANSI_COLOR_CYAN     "\x1b[1;36m" // Bold Cyan (Technology)
#define ANSI_COLOR_BLUE     "\x1b[0;34m" // Blue (Links/Details)
#define ANSI_COLOR_RESET    "\x1b[0m"    // Reset all formatting

void print_project(const char *title, const char *tech, const char *desc, const char *link) {
    printf(ANSI_COLOR_GREEN "  > %s\n" ANSI_COLOR_RESET, title);
    printf(ANSI_COLOR_CYAN "    Tech Stack: %s\n" ANSI_COLOR_RESET, tech);
    printf("    Description: %s\n", desc);
    if (link && *link) {
        printf(ANSI_COLOR_BLUE "    Link/Repo: %s\n\n" ANSI_COLOR_RESET, link);
    } else {
        printf("\n");
    }
}

int main() {
    printf(ANSI_COLOR_YELLOW "\n--- Key Technical Projects ---\n\n" ANSI_COLOR_RESET); 

    print_project(
        "Custom RTOS Scheduler (Cortex-M)",
        "Embedded C, ARM Assembly, FreeRTOS Concepts, STM32",
        "Implemented a non-preemptive cooperative multitasking scheduler with task control blocks (TCBs) and context switching in ARM assembly to manage concurrent sensor tasks.",
        "https://github.com/user/rtos-project" 
    );

    print_project(
        "High-Speed Packet Sniffer",
        "C, Linux Sockets (libpcap), Multithreading",
        "Developed a custom network traffic analyzer capable of capturing and parsing raw Ethernet frames, IPv4, and TCP headers using low-level socket programming and pcap filtering.",
        "https://github.com/user/packet-sniffer"
    );

    print_project(
        "RISC-V Instruction Set Simulator",
        "C++, Object-Oriented Design (OOD), Memory Management",
        "Designed and implemented an instruction set simulator for the RV32I base integer ISA, including register file, ALU, and memory hierarchy simulation to execute compiled binaries.",
        "https://github.com/user/riscv-simulator"
    );
    
    printf("--------------------------------------\n");

    return 0; // Exit successfully
}
