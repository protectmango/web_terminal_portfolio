// core-logic/skills.c
#include <stdio.h>

void print_skill_category(const char *category, const char *details) {
    printf("\033[1;36m%s:\033[0m\n", category); // ANSI escape codes for Cyan/Bold
    printf("  \033[32m- %s\033[0m\n\n", details); // ANSI escape codes for Green
}

int main() {
    printf("\n\033[1;33m--- Core Technical Proficiencies ---\033[0m\n\n"); // Yellow/Bold Heading

    print_skill_category(
        "C & Embedded C",
        "Expertise in pointer arithmetic, memory management (malloc/free), RTOS concepts, microcontroller peripherals (I2C, SPI, UART), and low-level driver development."
    );

    print_skill_category(
        "C++ & Object-Oriented Design (OOD)",
        "Proficient in modern C++ (C++11/14/17), STL containers, RAII, polymorphism, template meta-programming, and developing performance-critical applications."
    );

    print_skill_category(
        "ARM Architecture & Assembly",
        "Deep understanding of the ARM instruction set, memory models, interrupt handling, register usage, and optimizing code for Cortex-M/A series microprocessors."
    );

    print_skill_category(
        "Linux Programming & Systems Calls",
        "Fluent in using core Linux APIs: process management (fork, exec), inter-process communication (IPC) via shared memory, semaphores, and signals. Skilled in debugging with GDB."
    );

    print_skill_category(
        "TCPIP & Socket Programming",
        "Strong foundation in the OSI model. Expertise in creating custom network applications using TCP/UDP sockets in C, handling non-blocking I/O (epoll/select), and analyzing protocols (HTTP, FTP, DNS)."
    );
    
    printf("------------------------------------------\n");

    return 0; // Exit successfully
}
