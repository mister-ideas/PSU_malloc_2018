/*
** EPITECH PROJECT, 2019
** PSU_2018_malloc
** File description:
** free
*/

#include <unistd.h>
#include "malloc.h"

chunk_t *chunk_fusion(chunk_t *chunk)
{
    if (chunk->next && chunk->next->is_free) {
        chunk->data_size += sizeof(struct chunk) + chunk->next->data_size;
        chunk->next = chunk->next->next;
        if (chunk->next)
            chunk->next->prev = chunk;
    }
    return (chunk);
}

int check_adress(void *ptr)
{
    chunk_t *head = start;

    while (head) {
        if (head->end == ptr)
            return (1);
        head = head->next;
    }
    return (0);
}

void free(void *ptr)
{
    chunk_t *chunk = NULL;

    if (check_adress(ptr) == 1) {
        chunk = (chunk_t*)(ptr -= sizeof(struct chunk));
        chunk->is_free = 1;
        if (chunk->prev && chunk->prev->is_free)
            chunk = chunk_fusion(chunk->prev);
        if (chunk->next)
            chunk_fusion(chunk);
        else {
            if (chunk->prev)
                chunk->prev->next = NULL;
            else
                start = NULL;
            brk(chunk);
        }
    }
}
