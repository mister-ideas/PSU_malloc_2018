/*
** EPITECH PROJECT, 2019
** PSU_2018_malloc
** File description:
** realloc
*/

#include <string.h>
#include "malloc.h"

void *realloc(void *ptr, size_t size)
{
    chunk_t *chunk = NULL;
    chunk_t *new = NULL;
    void *new_end = NULL;

    size = (size - 1) / 4 * 4 + 4;
    if (check_adress(ptr) == 1) {
        chunk = (chunk_t*)(ptr -= sizeof(struct chunk));
        if (chunk->data_size >= size
        && chunk->data_size - size >= sizeof(struct chunk) + 4) {
            split_chunk(chunk, size);
            return (ptr);
        } else {
            new_end = malloc(size);
            if (!new_end)
                return (NULL);
            new = (chunk_t*)(new_end -= sizeof(struct chunk));
            memmove(new->end, chunk->end, new->data_size);
            free(chunk->end);
            return (new->end);
        }
    }
    return (NULL);
}