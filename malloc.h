/*
** EPITECH PROJECT, 2019
** PSU_2018_malloc
** File description:
** malloc
*/

#ifndef MALLOC_H_
#define MALLOC_H_

#include <stdio.h>

typedef struct chunck chunck_t;
struct chunck {
    size_t data_size;
    int is_free;
    chunck_t *next;
};

static void *start = NULL;

//malloc.c
void *malloc(size_t size);

#endif
