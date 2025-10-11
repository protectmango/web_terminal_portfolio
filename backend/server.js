// backend/server.js
const express = require('express');
const { Worker } = require('worker_threads');
const path = require('path');

const app = express();
const PORT = 3000;

// Middleware to parse JSON bodies
app.use(express.json());
// Serve static files from the 'frontend' directory
app.use(express.static(path.join(__dirname, '..', 'frontend')));

// --- API Endpoint to Process Commands ---
app.post('/api/command', (req, res) => {
    // Get the full command string from the user (e.g., "whois google.com")
    const command = req.body.command ? req.body.command.trim() : '';

    if (!command) {
        return res.json({ output: '', status: 'success' });
    }

    // Safely extract the primary command name (e.g., "whois")
    const commandParts = command.split(/\s+/);
    const safeCommand = commandParts[0].toLowerCase();

    // --- Command Routing and Execution ---
    let executablePath = '';

    // IMPORTANT: Check for recognized C executables in core-logic
    switch (safeCommand) {
        case 'help':
        case 'skills':
        case 'netstat':
        case 'resume':
        case 'dns_resolve':
        case 'projects':
        case 'whois': // <--- NEW: Recognized whois command
            // Constructs the path to the executable, e.g., ../core-logic/whois
            executablePath = path.join(__dirname, '..', 'core-logic', safeCommand);
            break;
        case 'clear':
            // Client-side command handled for safety
            return res.json({ output: '', status: 'success' });
        default:
            return res.status(404).json({
                output: `zsh: command not found: ${command}`,
                status: 'error'
            });
    }

    // --- NEW: Handle Arguments and Construct Full Execution String ---
    // If the user entered "whois google.com", this creates:
    // "./core-logic/whois google.com"
    const commandArguments = commandParts.slice(1).join(' ');
    const fullCommandToExecute = `${executablePath} ${commandArguments}`.trim();

    // --- Execute command in a separate Worker Thread ---
    const worker = new Worker(path.join(__dirname, 'commandWorker.js'), {
        workerData: { // Data passed to the worker
            command: safeCommand,
            fullCommand: fullCommandToExecute // <--- PASSING THE FULL COMMAND
        }
    });

    // Listener for messages (results) coming back from the worker thread
    worker.on('message', (result) => {
        if (result.status === 'success') {
            // Success: send the C program's stdout back to the frontend
            res.json({ output: result.output.trim(), status: 'success' });
        } else {
            // Send back errors
            res.status(500).json(result);
        }
    });

    // Listener for worker thread errors
    worker.on('error', (err) => {
        console.error(`Worker thread execution error for ${safeCommand}:`, err);
        res.status(500).json({
            output: `Internal Thread Error: ${err.message}`,
            status: 'error'
        });
    });

    // Clean up worker on exit
    worker.on('exit', (code) => {
        if (code !== 0) {
            console.warn(`Worker stopped with exit code ${code}`);
        }
    });
});

app.listen(PORT, () => {
    console.log(`Server running at http://localhost:${PORT}`);
    console.log(`Web terminal accessible at http://localhost:${PORT}/index.html`);
});
