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


#ifndef LISTLIB_H
#define LISTLIB_H

    #include <stddef.h>

    #define LIST(type, size)                __ListNew__(size, sizeof(type))
    #define LIST_PUSH(list, item)           __ListPushItem__(&list, item)
    #define LIST_GET(list, index, type)     *(type*)(__ListGetItem__(&list, index))
    #define LIST_POP(list, index)           __ListPopItem__(&list, index)
    #define LIST_CLEAR(list)                __listClear__(&list)
    #define LIST_LEN(list)                  __ListGetLength__(&list)
    #define LIST_SIZE(list)                 __ListGetBufferSize__(&list)
    #define LIST_DELETE(list)               __ListDelete__(&list)

    
    typedef struct List {
              void   *buffer;      // List buffer
              size_t  buffsize;    // Buffer size in bytes
              size_t  idx;         // List index
        const size_t  typesize;    // Size of the vector type
        const size_t  origsize;    // Original size of the list (In bytes)
    } list_t;


    list_t __ListNew__(size_t size, size_t typesize);
    void __ListInternalAppendItem__(list_t *list, void *item);
    void* __ListGetItem__(list_t *list, size_t index);
    void __ListPushItem__(list_t *list, ...);
    void __ListPopItem__(list_t *list, size_t index);
    void __ListDelete__(list_t *list);
    void __listClear__(list_t *list) ;
    size_t __ListGetLength__(list_t *list);
    size_t __ListGetBufferSize__(list_t *list);

#endif // LISTLIB_H
