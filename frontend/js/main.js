/**
 * main.js
 * Contains all the client-side logic for the web terminal interface.
 * Handles DOM manipulation, command history, ANSI color parsing, and API communication.
 */

// Polyfill for environments where crypto.randomUUID is not available (like older iFrames)
if (typeof crypto.randomUUID === 'undefined') {
    crypto.randomUUID = () => {
        let d = new Date().getTime();
        const uuid = 'xxxxxxxx-xxxx-4xxx-yxxx-xxxxxxxxxxxx'.replace(/[xy]/g, function (c) {
            const r = (d + Math.random() * 16) % 16 | 0;
            d = Math.floor(d / 16);
            return (c === 'x' ? r : (r & 0x3 | 0x8)).toString(16);
        });
        return uuid;
    };
}

// Initialize ansi_up globally, assuming the external script tag is present in index.html.
const ansi_up = new AnsiUp();
const outputDiv = document.getElementById('output');
const inputField = document.getElementById('command-input');
const promptSpan = document.getElementById('prompt'); // Get the prompt span element
const promptText = promptSpan ? promptSpan.textContent : 'user@portfolio:~ $'; // Fallback if ID is missing

const commandHistory = [];
let historyIndex = -1;
let isProcessing = false;
let isInitialLoad = true; // Flag to suppress command echo for 'banner'

// Unique Session ID (for potential debugging/identification, if needed)
const sessionId = crypto.randomUUID();

// --- Core Terminal Functions ---

/**
 * Appends a new line of text to the terminal output, processing ANSI codes.
 * Note: Assumes output is displayed in a container designed for pre-formatted text (like <pre> in the HTML).
 * @param {string} text - The text content to display.
 * @param {string} type - 'input', 'output', or 'error' for formatting.
 */
function appendOutput(text, type = 'output') {
    let content = '';

    if (type === 'input') {
        // For user input, print the full command line for history inside <pre>
        content = `${promptText}${text}`;
    } else if (type === 'error') {
        // Use ANSI red for errors before piping through ansi_up
        const errorText = `\x1b[1;31mError:\x1b[0m ${text}`;
        content = ansi_up.ansi_to_html(errorText);
    } else {
        // General output: use ansi_up to convert C output to HTML
        content = ansi_up.ansi_to_html(text);
    }

    // Append the new content wrapped in <pre> tags to match the HTML structure
    outputDiv.innerHTML += `<pre>${content}</pre>`;

    // Scroll to the bottom of the output area
    outputDiv.scrollTop = outputDiv.scrollHeight;
}

// --- Command Handling ---

/**
 * Sends the command to the backend API for execution.
 * @param {string} command - The full command string.
 * @param {boolean} echoCommand - Whether to echo the command line before execution.
 */
async function sendCommand(command, echoCommand = true) {
    // Only proceed if a command isn't already being processed
    if (isProcessing) return;

    isProcessing = true;

    // 1. Display user input in the output area (if echo is requested)
    if (echoCommand) {
        appendOutput(command, 'input');
    }

    // 2. Clear input field
    inputField.value = '';

    try {
        const response = await fetch('/api/command', {
            method: 'POST',
            headers: { 'Content-Type': 'application/json' },
            body: JSON.stringify({ command: command })
        });

        const data = await response.json();

        if (response.ok && data.status === 'success') {
            // 'clear' command is handled client-side
            if (command.trim() === 'clear') {
                // Now only clears the output, leaving the prompt below it.
                outputDiv.innerHTML = '';
            } else if (data.output) {
                // Trim to remove leading/trailing newlines that <pre> might double-up
                appendOutput(data.output.trim(), 'output');
            }
        } else {
            // Handle API errors or C execution errors returned from the server
            appendOutput(data.output || 'Unknown error occurred.', 'error');
        }

    } catch (error) {
        console.error('Fetch error:', error);
        appendOutput(`Network Error: Could not reach the server. Is the backend running? (${error.message})`, 'error');
    } finally {
        isProcessing = false;

        // This is crucial: after the initial banner, we set the flag to false
        if (command.toLowerCase() === 'banner' && isInitialLoad) {
            isInitialLoad = false;
        }

        // Always refocus the input
        inputField.focus();
    }
}

/**
 * Processes the command when the user hits Enter.
 */
function processInput() {
    if (isProcessing) return;

    const command = inputField.value.trim();
    if (command === '') {
        // If input is empty, do nothing, the prompt is already visible
        return;
    }

    // Add to history
    if (commandHistory[commandHistory.length - 1] !== command) {
        commandHistory.push(command);
    }
    historyIndex = commandHistory.length; // Reset index to the end

    // Send command to backend (echoCommand is always true for user input)
    sendCommand(command, true);
}


// --- Event Listeners ---

document.addEventListener('keydown', (e) => {
    // 1. CLEAR SCREEN SHORTCUTS: Cmd/Ctrl + L/K
    const isCtrlCmdL = (e.key.toLowerCase() === 'l' && (e.ctrlKey || e.metaKey));
    const isCtrlCmdK = (e.key.toLowerCase() === 'k' && (e.ctrlKey || e.metaKey));

    if (isCtrlCmdL || isCtrlCmdK) {
        e.preventDefault();
        // Clear the screen completely, showing only the prompt line below.
        outputDiv.innerHTML = '';
        inputField.value = '';
        inputField.focus();
        return;
    }

    // Only process other keys if the input field is focused
    if (document.activeElement !== inputField) return;

    // 2. COMMAND HISTORY NAVIGATION
    if (e.key === 'Enter') {
        processInput();
    } else if (e.key === 'ArrowUp') {
        e.preventDefault(); // Prevent cursor movement
        if (commandHistory.length > 0 && historyIndex > 0) {
            historyIndex--;
            inputField.value = commandHistory[historyIndex];
        }
    } else if (e.key === 'ArrowDown') {
        e.preventDefault(); // Prevent cursor movement
        if (historyIndex < commandHistory.length - 1) {
            historyIndex++;
            inputField.value = commandHistory[historyIndex];
        } else if (historyIndex === commandHistory.length - 1) {
            // If at the end, set to empty string but keep history index
            historyIndex = commandHistory.length;
            inputField.value = '';
        }
    }
});

// Set focus and run initial command on page load
document.addEventListener('DOMContentLoaded', () => {
    inputField.focus();

    // Execute the banner command immediately upon load.
    // The second argument 'false' ensures the 'banner' command line is NOT echoed.
    sendCommand('banner', false);
});

