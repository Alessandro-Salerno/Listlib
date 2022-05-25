#ifndef LISTLIB_H
#define LISTLIB_H

    #define LIST(type, size)                __ListNew__(size, sizeof(type))
    #define LIST_PUSH(list, item)           __ListPushItem__(&list, item)
    #define LIST_GET(list, index, type)     *(type*)(__ListGetItem__(&list, index))
    #define LIST_POP(list, index)           __ListPopItem__(&list, index)
    #define LIST_CLEAR(list)                __listClear__(&list)
    #define LIST_LEN(list)                  __ListGetLength__(&list)
    #define LIST_SIZE(list)                 __ListGetBufferSize__(&list)
    #define LIST_DELETE(list)               __ListDelete__(&list)

    
    typedef struct List list_t;


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
