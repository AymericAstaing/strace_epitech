/*
** EPITECH PROJECT, 2018
** print_simple_syscall.c
** File description:
** syscall simple output
*/

#include <stdlib.h>
#include <sys/user.h>
#include <stdio.h>
#include <syscall_mapping.h>
#include "../include/strace.h"

void print_simple_syscall(struct user_regs_struct *regs)
{
    int i = 0;
    int sys_code = regs->rax;

    int arg_nbr = sys_proto[sys_code].params_nbr;
    print_syscall_name(sys_code);
    printf("(");
    for (; i < arg_nbr - 1; i++) {
        printf("0x%llx, ", get_register_value(i, regs));
    }
    printf("0x%llx)", get_register_value(i, regs));
}
