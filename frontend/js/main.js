// frontend/js/main.js

// Initialize ansi_up globally. This requires the script tag in index.html.
const ansi_up = new AnsiUp();

document.addEventListener('DOMContentLoaded', () => {
    const input = document.getElementById('command-input');
    const output = document.getElementById('output');
    // Get the prompt text once, e.g., "user@portfolio:~$ "
    const promptText = document.getElementById('prompt').textContent;

    // Set initial focus
    input.focus();

    input.addEventListener('keydown', function(event) {
        if (event.key === 'Enter') {
            const command = input.value.trim();
            input.value = ''; // Clear input field
            processCommand(command);
        }
    });


    // --- Keyboard Shortcut Handler (Ctrl+L, Cmd+K, Cmd+L) ---
    document.addEventListener('keydown', function(event) {
        let isCtrlKey = event.ctrlKey;
        let isCmdKey = event.metaKey; // event.metaKey is the Command key on Mac

        // Check for Ctrl+L (common Linux/Windows clear)
        // OR Cmd+K / Cmd+L (common Mac clear)
        if (
            (isCtrlKey && event.key === 'l') ||
            (isCmdKey && (event.key === 'k' || event.key === 'l'))
        ) {
            // Prevent the browser's default action (e.g., Ctrl+L focusing the address bar)
            event.preventDefault();

            // Execute the client-side 'clear' logic directly
            // Note: We replicate the logic from processCommand('clear') here
            output.innerHTML = '';
            output.innerHTML = `<pre>Welcome back. Type 'help' for commands.</pre><pre></pre>`;

            input.focus(); // Ensure focus returns to the input
        }
    });

    // Keep the input focused when clicking anywhere in the terminal area
    document.getElementById('terminal').addEventListener('click', () => {
        input.focus();
    });

    /**
     * Appends text to the terminal output, processing ANSI codes.
     * @param {string} text - The text to display (may contain ANSI codes).
     * @param {boolean} isCommand - True if the text is the command line itself.
     */
    function displayOutput(text, isCommand = false) {
        // If it's the command, display the prompt and the command typed as plain text
        if (isCommand) {
             output.innerHTML += `<pre>${promptText}${text}</pre>`;
        } else {
            // CORE CHANGE: Use ansi_up to convert ANSI codes (like \x1b[32m) to HTML (<span> tags)
            let formattedText = ansi_up.ansi_to_html(text);

            if (text) {
                // Use innerHTML because formattedText now contains HTML span tags for color
                output.innerHTML += `<pre>${formattedText}</pre>`;
            } else {
                output.innerHTML += `<pre></pre>`;
            }
        }

        // Scroll to the very bottom to show the latest output
        output.scrollTop = output.scrollHeight;
    }

    function processCommand(command) {
        if (!command) {
            displayOutput('', true); // Just show the prompt
            return;
        }

        displayOutput(command, true); // Display the command typed

        // --- Client-side command ---
        if (command.toLowerCase() === 'clear') {
            output.innerHTML = '';
            // Re-display the welcome message for clarity after a clear
            output.innerHTML = `<pre>Welcome back. Type 'help' for commands.</pre><pre></pre>`;
            return;
        }

        // --- Backend Communication via Fetch API (Concurrent Execution) ---
        fetch('/api/command', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json',
            },
            body: JSON.stringify({ command: command }),
        })
        .then(response => {
            // Check for non-OK status (4xx or 5xx)
            if (!response.ok) {
                // If it's an error, parse the body to get the custom error message
                return response.json().then(data => {
                    // Throw the custom error message from the server
                    throw new Error(data.output || 'Server responded with an unexpected error.');
                });
            }
            return response.json();
        })
        .then(data => {
            // Success: display the output captured from the C program
            displayOutput(data.output.trim());
        })
        .catch(error => {
            // Display any network failure or server-side execution error
            // Use ANSI red for error messages for style
            displayOutput(`\x1b[1;31mError:\x1b[0m ${error.message || 'Network request failed.'}`);
        });
    }
});
