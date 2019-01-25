/*
** EPITECH PROJECT, 2019
** PSU_2018_malloc
** File description:
** malloc
*/

#include <unistd.h>
#include <stdio.h>
#include "malloc.h"

void *start = NULL;

void split_chunk(chunk_t *chunk, size_t size)
{
    chunk_t *new;

    new = chunk + sizeof(struct chunk) + size;
    new->data_size = chunk->data_size - (sizeof(struct chunk) + size);
    new->next = chunk->next;
    new->is_free = 1;
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
    chunk_t *new;

    while (head)
        head = head->next;
    new = sbrk(0);
    if (!new || sbrk(sizeof(struct chunk) + size) == (void *) -1)
        return (NULL);
    new->data_size = size;
    new->next = NULL;
    if (start)
        head->next = new;
    else
        start = new;
    return (new);
}

void *malloc(size_t size)
{
    chunk_t *new;

    if (start) {
        printf("MALLOC: not null\n");
        new = find_free_chunk(size);
        if (new) {
            if (new->data_size - size > sizeof(struct chunk) + 4)
                split_chunk(new, size);
            new->is_free = 0;
        } else {
            new = extend_heap(size);
            if (!new)
                return (NULL);
        }
    } else {
        new = extend_heap(size);
        if (!new)
            return (NULL);
        start = new;
    }
    return (new);
}
