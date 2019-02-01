/*
** EPITECH PROJECT, 2019
** PSU_2018_malloc
** File description:
** malloc
*/

#include <unistd.h>
#include "malloc.h"

void *start = NULL;

void split_chunk(chunk_t *chunk, size_t size)
{
    chunk_t *new = NULL;

    new = (chunk_t *)(chunk->end + size);
    new->end = chunk->end + size + sizeof(struct chunk);
    new->data_size = chunk->data_size - (sizeof(struct chunk) + size);
    new->next = chunk->next;
    new->prev = chunk;
    new->is_free = 1;
    if (new->next)
        new->next->prev = new;
    chunk->data_size = size;
    chunk->next = new;
}

chunk_t *find_free_chunk(size_t size)
{
    chunk_t *head = start;

    while (head) {
        if (head->data_size >= size && head->is_free == 1)
            return (head);
        head = head->next;
    }
    return (NULL);
}

chunk_t *extend_heap(size_t size)
{
    chunk_t *head = start;
    chunk_t *new = NULL;

    new = sbrk(0);
    if (!new || sbrk(sizeof(struct chunk)) == (void *) -1)
        return (NULL);
    new->end = sbrk(size);
    if (new->end == (void *) -1)
        return (NULL);
    new->data_size = size;
    new->next = NULL;
    new->is_free = 0;
    while (head && head->next)
        head = head->next;
    if (start) {
        new->prev = head;
        head->next = new;
    } else {
        new->prev = NULL;
        start = new;
    }
    return (new);
}

void *malloc(size_t size)
{
    chunk_t *new = NULL;

    size = ((((size - 1) >> 3) << 3) + 8);
    new = find_free_chunk(size);
    if (new) {
        if (new->data_size - size > sizeof(struct chunk) + 8)
            split_chunk(new, size);
        new->is_free = 0;
    } else {
        new = extend_heap(size);
        if (!new)
            return (NULL);
    }
    return (new->end);
}
