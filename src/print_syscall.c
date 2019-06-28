/*
** EPITECH PROJECT, 2018
** print_syscall.c
** File description:
** syscall output
*/

#include <sys/user.h>
#include <stdio.h>
#include <string.h>
#include <sys/ptrace.h>
#include <string.h>
#include "strace.h"
#include "syscall_mapping.h"

void print_syscall_name(int syscall_code)
{
    printf("%s", sys_proto[syscall_code].name);
}

void display_arg_output(char *type, int arg_id, pid_t pid,
struct user_regs_struct *regs)
{
    int i = 0;

    if (is_pointer(type)) {
        print_pointer(pid, get_register_value(arg_id, regs));
        return;
    } 
    while (arg_type[i + 1].type != NULL &&
    strcmp(arg_type[i].type, type) != 0)
        i++;
    arg_type[i].print_value(pid, get_register_value(arg_id, regs));
}

void display_return_value(int sysc_code, struct user_regs_struct *regs, int complex)
{
    char *ret_type = sys_proto[sysc_code].ret_type;

    printf(" = ");
    if (complex == 0) {
        printf("0x%llx\n", get_register_value(-1, regs));
        return;
    }
    if (is_end(sysc_code)) {
        printf("?\n");
        return;
    }
    if ((long long) regs->rax < 0)
	    printf("-1 (%s)", strerror(-regs->rax));
    else
        display_arg_output(ret_type, -1, -1, regs);
    printf("\n");
}

void print_syscall_args(int sysc_code, pid_t pid, struct user_regs_struct *regs)
{
    int i = 0;
    int arg_nbr = sys_proto[sysc_code].params_nbr;

    for (; i < arg_nbr - 1; i++) {
        display_arg_output(sys_proto[sysc_code].params[i], i, pid, regs);
        printf(", ");
    }
    display_arg_output(sys_proto[sysc_code].params[i], i, pid, regs);
}

void print_syscall(int call_code, struct user_regs_struct *regs, pid_t child)
{
    print_syscall_name(call_code);
    printf("(");
    if (call_code == 59)
        printf("\"\", \"\", \"\"");
    else
        print_syscall_args(call_code, child, regs);
    printf(")");
}