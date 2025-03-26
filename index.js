const memoryAlloc = require('./build/Release/memory_alloc.node');

const pointer = memoryAlloc.allocateCharArray();

console.log('Allocated char array pointer:', pointer);

memoryAlloc.setCharArray(pointer, 0, 65);

const value = memoryAlloc.getCharArray(pointer, 0);

console.log('Value at offset 0:', value);

const str = "Hellt";
for (let i = 0; i < str.length; i++) {
    memoryAlloc.setCharArray(pointer, i, str.charCodeAt(i));
}

let result = "";
for (let i = 0; i < str.length; i++) {
    result += String.fromCharCode(memoryAlloc.getCharArray(pointer, i));
}

console.log("String from char array:", result);