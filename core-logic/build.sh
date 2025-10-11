#!/bin/bash
# A simple script to compile the core C programs

CC="gcc"
C_FLAGS="-Wall -Wextra -std=c99"
OUTPUT_DIR="./"

echo "--- Compiling C Core Logic ---"

# Compile help.c
echo "Compiling help.c..."
$CC $C_FLAGS help.c -o $OUTPUT_DIR/help
if [ $? -eq 0 ]; then
    echo "SUCCESS: help executable created."
else
    echo "ERROR: Failed to compile help.c"
    exit 1
fi

# Compile skills.c (NEW ADDITION)
echo "Compiling skills.c..."
$CC $C_FLAGS skills.c -o $OUTPUT_DIR/skills
if [ $? -eq 0 ]; then
    echo "SUCCESS: skills executable created."
else
    echo "ERROR: Failed to compile skills.c"
    exit 1
fi

# Compile whois.c (NEW ADDITION)
echo "Compiling whois.c..."
# Adding -lncurses and -lc is sometimes necessary for older systems/specific libraries,
# but for basic sockets, standard gcc should work.
# If compilation fails, try: $CC $C_FLAGS whois.c -o $OUTPUT_DIR/whois -lncurses
$CC $C_FLAGS whois.c -o $OUTPUT_DIR/whois
if [ $? -eq 0 ]; then
    echo "SUCCESS: whois executable created."
else
    echo "ERROR: Failed to compile whois.c"
    exit 1
fi

# Compile dns_resolve.c (NEW ADDITION)
echo "Compiling dns_resolve.c..."
# We link against the resolve library for DNS helper functions
$CC $C_FLAGS dns_resolve.c -o $OUTPUT_DIR/dns_resolve -lresolv
if [ $? -eq 0 ]; then
    echo "SUCCESS: dns_resolve executable created."
else
    echo "ERROR: Failed to compile dns_resolve.c"
    exit 1
fi


# Compile projects.c (NEW ADDITION)
echo "Compiling projects.c..."
$CC $C_FLAGS projects.c -o $OUTPUT_DIR/projects
if [ $? -eq 0 ]; then
    echo "SUCCESS: projects executable created."
else
    echo "ERROR: Failed to compile projects.c"
    exit 1
fi

# Compile netstat.c (NEW ADDITION)
echo "Compiling netstat.c..."
$CC $C_FLAGS netstat.c -o $OUTPUT_DIR/netstat
if [ $? -eq 0 ]; then
    echo "SUCCESS: netstat executable created."
else
    echo "ERROR: Failed to compile netstat.c"
    exit 1
fi

# Compile download.c (NEW ADDITION: Resume)
echo "Compiling resume.c..."
$CC $C_FLAGS resume.c -o $OUTPUT_DIR/resume
if [ $? -eq 0 ]; then
    echo "SUCCESS: resume executable created."
else
    echo "ERROR: Failed to compile resume.c"
    exit 1
fi

echo "--- Compilation Complete ---"
