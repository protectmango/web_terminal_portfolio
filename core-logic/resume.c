// core-logic/download.c
#include <stdio.h>

#define ANSI_COLOR_RED      "\x1b[1;31m"
#define ANSI_COLOR_CYAN     "\x1b[1;36m"
#define ANSI_COLOR_YELLOW   "\x1b[1;33m"
#define ANSI_COLOR_GREEN    "\x1b[0;32m"
#define ANSI_COLOR_RESET    "\x1b[0m"

void print_section_header(const char *title) {
    printf(ANSI_COLOR_YELLOW "\n%s\n" ANSI_COLOR_RESET, title);
    printf("----------------------------------------------------------------\n");
}

int main() {
    // -------------------------------------------------------------------
    // 1. HEADER (Contact Info)
    // -------------------------------------------------------------------
    printf(ANSI_COLOR_GREEN "\n\t\t\tGULSHAN KUMAR RANA\n" ANSI_COLOR_RESET);
    printf("\t\t\t" "Embedded Trainee Engineer\n");
    printf("\t\t\t7042885337 | gulshanrana21.1974@gmail.com | GitHub: /protectmango\n");
    
    // -------------------------------------------------------------------
    // 2. PROFILE SUMMARY (Motivational Description - Keyword Rich)
    // -------------------------------------------------------------------
    print_section_header("PROFILE SUMMARY");
    printf("Highly motivated and dedicated individual with a strong foundation in " ANSI_COLOR_CYAN "C/C++" ANSI_COLOR_RESET " and a deep passion for " ANSI_COLOR_CYAN "Embedded Systems" ANSI_COLOR_RESET " and low-level programming. "
           "Eager to apply comprehensive knowledge of " ANSI_COLOR_CYAN "RTOS concepts, microcontrollers, and hardware-software interfacing" ANSI_COLOR_RESET " to contribute to innovative hardware development. "
           "Committed to continuous learning and delivering robust, efficient, and well-tested firmware solutions.\n");

    // -------------------------------------------------------------------
    // 3. CORE TECHNICAL SKILLS (Keyword Rich)
    // -------------------------------------------------------------------
    print_section_header("CORE TECHNICAL SKILLS");
    printf(ANSI_COLOR_YELLOW "Programming: " ANSI_COLOR_RESET "C (Expert), C++, Python, Shell Scripting, ARM Assembly.\n");
    printf(ANSI_COLOR_YELLOW "Embedded: " ANSI_COLOR_RESET "Microcontrollers (STM32, ESP32), RTOS (FreeRTOS, custom schedulers), Device Drivers, Hardware Debugging (JTAG/SWD).\n");
    printf(ANSI_COLOR_YELLOW "Interfacing: " ANSI_COLOR_RESET "I2C, SPI, UART, ADC, DAC, Timers, Interrupts/ISR programming.\n");
    printf(ANSI_COLOR_YELLOW "Networking: " ANSI_COLOR_RESET "TCP/IP, UDP, Sockets, Low-level Network Protocols, DNS.\n");
    printf(ANSI_COLOR_YELLOW "Tools/OS: " ANSI_COLOR_RESET "Git, CMake, Make, Linux, VS Code, PlatformIO.\n");
    
    // -------------------------------------------------------------------
    // 4. EDUCATION
    // -------------------------------------------------------------------
    print_section_header("EDUCATION");
    
    // Graduation Details
    printf(ANSI_COLOR_GREEN "GRADUATION: [Bachelor of Technology] in [ECE]\n" ANSI_COLOR_RESET);
    printf("  [RGPV/Rustamji Institute of Technology], [Gwalior/MP]\t\t\t\t\t\t" ANSI_COLOR_CYAN "[2024]\n" ANSI_COLOR_RESET);
    printf("  Key Courses: Embedded Systems Design, Computer Architecture, Data Structures, Operating Systems.\n\n");

    // Higher Secondary Details
    printf(ANSI_COLOR_GREEN "HIGHER SECONDARY (12th Grade)\n" ANSI_COLOR_RESET);
    printf("  [Kendriya Vidyalaya Masjid Moth, Sadiq Nagar], [New Delhi]\t\t\t\t\t" ANSI_COLOR_CYAN "[2019]\n" ANSI_COLOR_RESET);
    printf("  Focus: Mathematics, Physics, Chemistry/Computer Science.\n\n");
   
    // -------------------------------------------------------------------
    // 5. PROJECTS
    // -------------------------------------------------------------------
    print_section_header("SELECT EMBEDDED PROJECTS");
    printf("See the '" ANSI_COLOR_CYAN "projects" ANSI_COLOR_RESET "' command for details on the " ANSI_COLOR_YELLOW "Custom RTOS Scheduler" ANSI_COLOR_RESET ", " ANSI_COLOR_YELLOW "Packet Sniffer" ANSI_COLOR_RESET ", and " ANSI_COLOR_YELLOW "DNS Resolver" ANSI_COLOR_RESET ".\n\n");

     // Provide the link directly. The frontend HTML/CSS will recognize and style the URL.
    printf(ANSI_COLOR_GREEN "  The latest version of the resume is available for download:\n" ANSI_COLOR_RESET);

    // NOTE: This line MUST be updated with your actual hosted PDF link.
    // Ensure the link is wrapped in a way that your frontend correctly detects it as a URL.

    printf(ANSI_COLOR_CYAN "  __RESUME_LINK_START__resume.pdf__RESUME_LINK_END__\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_GREEN "\n  Thank you for your interest!\n" ANSI_COLOR_RESET);

    printf("\n" ANSI_COLOR_RED "Note: Feel free to contact through my mail or phone number.\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_CYAN "----------------------------------------------------------------\n\n" ANSI_COLOR_RESET);

    return 0;
}
