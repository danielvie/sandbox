// post.js

Module.onRuntimeInitialized = function () {
    // Code to run after the module is loaded
};

// Define the exported Julia function
var add_numbers = Module.cwrap('add_numbers', 'number', ['number', 'number']);
