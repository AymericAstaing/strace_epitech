/*
** EPITECH PROJECT, 2018
** print_type.c
** File description:
** print type nbr 1.c
*/

#include <stdio.h>
#include <err.h>
#include <errno.h>
#include <string.h>
#include <sys/ptrace.h>
#include "strace.h"

void print_not_implemented(pid_t pid, unsigned long long int reg_value)
{
    (void)reg_value;
    (void)pid;
    printf("unimplemented");
}

void do_nothing(pid_t pid, unsigned long long int reg_value)
{
    (void)pid;
    (void)reg_value;
}

void print_char(char c)
{
    if (c == '\0' || c == '\0')
        return;
    if (c >= 32 && c < 127) {
        printf("%c", c);
        return;
    }
    printf("\\%o", c);
}

void print_string(pid_t pid, unsigned long long int reg_value)
{
    int	i = 0;
    long c = -1;

    printf("\"");
    for (; (char) c != '\0' && i < 40; reg_value++, i++) {
        c = ptrace(PTRACE_PEEKDATA, pid, reg_value, NULL);
        print_char(c);
    }
    printf("\"");
}

void print_tab(pid_t pid, unsigned long long int reg_value)
{
    unsigned long long str = (unsigned long long) -1;
    int i = 0;

    printf("[");
    for (; (void *) str != NULL && i < 6; reg_value += sizeof(char*), i++) {
        str = ptrace(PTRACE_PEEKDATA, pid, reg_value, NULL);
        if (str > 0)
	          print_string(pid, str);
    }
    printf("]");
}