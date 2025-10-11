// backend/commandWorker.js
const { parentPort, workerData } = require('worker_threads');
const { exec } = require('child_process');

// Retrieve both the simple command name (for logging) and the full execution string
const { command, fullCommand } = workerData;

// The thread logic: execute the external C program using the full command string
// Example: fullCommand will be "./core-logic/whois google.com"
exec(fullCommand, (error, stdout, stderr) => {
    let result = {};

    if (error) {
        // C program not found or crashed
        console.error(`Worker Exec Error for ${command}: ${error.message}`);
        result = {
            output: `Execution failed: ${stderr || error.message}`,
            status: 'error'
        };
    } else if (stderr) {
        // C program printed to stderr
        result = {
            output: stderr,
            status: 'error'
        };
    } else {
        // Success
        result = {
            output: stdout,
            status: 'success'
        };
    }

    // Send the result back to the main thread (server.js)
    parentPort.postMessage(result);
});
