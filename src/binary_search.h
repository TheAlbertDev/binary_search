#ifndef _BINARY_SEARCH_H__
#define _BINARY_SEARCH_H__

#include <stddef.h>
#include <stdint.h>

typedef struct
{
    uint32_t tail;
    uint32_t head;
} Fifo_Indexes_t;

Fifo_Indexes_t init_fifo_indexes(uint32_t *arr, size_t size);

#endif