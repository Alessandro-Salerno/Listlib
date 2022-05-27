/********************************************************************************
MIT License

Copyright (c) 2022 Alessandro Salerno

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
********************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <memory.h>
#include <assert.h>
#include <stdarg.h>
#include <stdbool.h>


typedef struct List {
          void   *buffer;      // List buffer
          size_t  buffsize;    // Buffer size in bytes
          size_t  idx;         // List index
    const size_t  typesize;    // Size of the vector type
    const size_t  origsize;    // Original size of the list (In bytes)
} list_t;


list_t __ListNew__(size_t size, size_t typesize) {
    assert(size != 0);
    assert(typesize != 0);
    
    return (list_t) {
        .buffer   = calloc(size, typesize),
        .buffsize = size * typesize,
        .typesize = typesize,
        .origsize = size * typesize,
        .idx      = 0
    };
}

void __ListInternalAppendItem__(list_t *list, void *item) {
    assert(list->buffer != NULL);                // Checks if the buffer exists
    size_t offset = list->idx * list->typesize;  // Calculates the item's offset using the index and the type size
    
    // Allocates more memory if needed
    if (offset >= list->buffsize) {
        list->buffsize *= 2;
        list->buffer    = realloc(list->buffer, list->buffsize);
    }
    
    // Copies the item onto the buffer using the previously calculated offset
    memcpy((void*)((size_t)(list->buffer) + offset), item, list->typesize);
    list->idx++;
}

void* __ListGetItem__(list_t *list, size_t index) {
    size_t offset = index * list->typesize;     // Calculates the item's offset using the index and the type size
    assert(offset < list->buffsize);            // Prevents the function from going out of bound
    
    // Returns a pointer to the exact memory location where the item lives
    return (void*)((size_t)(list->buffer) + offset);
}

void __ListPushItem__(list_t *list, ...) {
    va_list args;
    
    va_start(args, list);
    __ListInternalAppendItem__(list, (void*)(args));
    va_end(args);
}

void __ListPopItem__(list_t *list, size_t index) {
    size_t offset = index * list->typesize;         // Offset where the item lives
    size_t idxoff = list->idx * list->typesize;     // Offset of the last index
    size_t next   = offset + list->typesize;        // Offset of the next item

    // Prevents the function from going of out b bound
    assert(next <= idxoff);

    // Moves everything down by one index and clears the memory left over by the pop
    memcpy((void*)((size_t)(list->buffer) + offset), (void*)((size_t)(list->buffer) + next), idxoff - next);
    memset((void*)((size_t)(list->buffer) + idxoff - list->typesize), 0, list->typesize);
    list->idx--;
}

void __ListDelete__(list_t *list) {
    // Checks if the list has already been deleted
    assert(list->buffer != NULL);
    assert(list->buffsize != 0);
    
    // Frees all memory and resets all fields
    free(list->buffer);
    list->buffer   = NULL;
    list->buffsize = 0;
    list->idx      = 0;
}

void __listClear__(list_t *list) {
    // Deallocates the entire buffer and allocates a new one with the original size
    free(list->buffer);
    list->buffer = calloc(list->origsize, 1);

    // Updates fields
    list->buffsize = list->origsize;
    list->idx      = 0;
}

size_t __ListGetLength__(list_t *list)      { return list->idx;      }
size_t __ListGetBufferSize__(list_t *list)  { return list->buffsize; }
