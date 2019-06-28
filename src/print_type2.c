/*
** EPITECH PROJECT, 2018
** print_type.c
** File description:
** print type nbr 2.c
*/

#include <stdio.h>
#include "strace.h"

void print_int(pid_t pid, unsigned long long int reg_value)
{
    (void)pid;
    printf("%d", (int) reg_value);
}

void print_long(pid_t pid, unsigned long long int reg_value)
{
    (void)pid;
    printf("%ld", (long) reg_value);
}

void print_un_int(pid_t pid, unsigned long long int reg_value)
{
    (void)pid;
    printf("%u", (unsigned int) reg_value);
}

void print_un_long(pid_t pid, unsigned long long int reg_value)
{
    (void)pid;
    printf("%lu", (unsigned long) reg_value);
}

void print_pointer(pid_t pid, unsigned long long int reg_value)
{
    (void)pid;
    if (reg_value == 0) {
        printf("NULL");
        return;
    }
    printf("%p", (void *) reg_value);
}