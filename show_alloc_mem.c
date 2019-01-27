/*
** EPITECH PROJECT, 2019
** PSU_2018_malloc
** File description:
** show_alloc_mem
*/

#include <unistd.h>
#include "malloc.h"

void show_alloc_mem()
{
    chunk_t *head = start;

    printf("break : %p\n", sbrk(0));
    if (!head)
        start = NULL;
    while (head) {
        if (head->next)
            printf("%p - %p : %zu bytes\n", head, head->next, head->data_size);
        else
            printf("%p - %p : %zu bytes\n", head, sbrk(0), head->data_size);
        head = head->next;
    }
}
