/*
** EPITECH PROJECT, 2019
** PSU_2018_malloc
** File description:
** malloc
*/

#ifndef MALLOC_H_
#define MALLOC_H_

#include <stdio.h>

typedef struct chunk chunk_t;
struct chunk {
    size_t data_size;
    int is_free;
    void *end;
    chunk_t *next;
};

extern void *start;

//malloc.c
void *malloc(size_t size);
chunk_t *extend_heap(size_t size);
chunk_t *find_free_chunk(size_t size);
void split_chunk(chunk_t *chunk, size_t size);

//free.c
void free(void *ptr);

//show_alloc_mem.c
void show_alloc_mem();

#endif
