#include "minicrt.h"

typedef struct _heap_header
{
    enum{
        HEAP_BLOCK_FREE = 0xABABABAB,
        HEAP_BLOCK_USED = 0xCDCDCDCD,
    }type;
    unsigned size;
    struct _heap_header *next;
    struct _heap_header *prev;
}heap_header;

#define ADDR_ADD(a, o) (((char *)(a)) + o)
#define header_size (sizeof(heap_header))

static heap_header *list_head = NULL;

#ifndef WIN32
static int brk(void* end_data_segment)
{
    int ret = 0;
    asm(
        "movl $214, %%eax\n\t"
        "movl %1, %%ebx\n\t"
        "int $0x80 \n\t"
        "movl %%eax, %0 \n\t"
        : "=r"(ret): "m"(end_data_segment)
    );
    //return ret;0x08048406 in mini_crt_heap_init ()
}
#endif

void *malloc(unsigned size)
{
    heap_header *header;

    if(size == 0)
        return NULL;

    header = list_head;

    while(header != 0)
    {
        if(header->type == HEAP_BLOCK_USED)
        {
            header = header->next;
            continue;
        }
        if(header->size > size + header_size && header->size <= size + header_size*2)
        {
            header->type = HEAP_BLOCK_USED;
        }
        if(header->size > size + header_size*2)
        {
            heap_header *next = (heap_header *)ADDR_ADD(header, size + header_size);
            next->prev = header;
            next->next = header->next;
            next->type = HEAP_BLOCK_FREE;
            next->size = header->size-(size-header_size);
            header->next = next;
            header->size = size+header_size;
            header->type = HEAP_BLOCK_USED;
            return ADDR_ADD(header, header_size);
        }
        header = header->next;
    }
    return NULL;
}


void free(void *ptr)
{
    heap_header * header = (heap_header *)ADDR_ADD(ptr, -header_size);
    if(header->type != HEAP_BLOCK_USED)
        return;

    header->type = HEAP_BLOCK_FREE;
    if(header->prev != NULL && header->prev->type == HEAP_BLOCK_FREE)
    {
        //merge
        header->prev->next = header->next;
        if(header->next != NULL)
            header->next->prev = header->prev;
        header->prev->size += header->size;

        header = header->prev;
    }

    if(header->next != NULL && header->next->type == HEAP_BLOCK_FREE)
    {
        header->size += header->next->size;
        header->next = header->next->next;
    }
}

#ifdef WIN32
#include <Windows.h>
#endif

//heap init
int mini_crt_heap_init(void)
{
    void *base = NULL;

    heap_header *header = NULL;
    unsigned heap_size = 1024*1024*32;//32M

#ifdef WIN32
    base = VirtualAlloc(0, heap_size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    if(NULL == base)
        return 0;
#else
    base = (void *)brk(0);
    void *end=ADDR_ADD(base , heap_size);
    end = (void *)brk(end);
    if(!end)
        return 0;
#endif

    header = (heap_header *)base;

    header->size = heap_size;
    header->type = HEAP_BLOCK_FREE;
    header->next = NULL;
    header->prev = NULL;

    list_head = header;

    return 1;
}