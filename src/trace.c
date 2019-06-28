/*
** EPITECH PROJECT, 2018
** trace.c
** File description:
** trace.c
*/

#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/ptrace.h>
#include <sys/reg.h>
#include <sys/user.h>
#include <stdio.h>
#include "../include/strace.h"


int	resume_process(pid_t pid, int *status)
{
    if (ptrace(PTRACE_SINGLESTEP, pid, NULL, NULL) == -1)
        return (1);
    waitpid(pid, status, 0);
    return (0);
}

void end_of_execution(int sys_code)
{
    if (is_end(sys_code)) {
        system("echo -n +++ exited with $? +++");
        printf("\n");
        exit(0);
    }
}

int syscall_manager(struct user_regs_struct *regs, pid_t child,
int* status, int complex_output)
{   

    int sys_code = regs->rax;
    
    if (sys_code > 313)
        return (1);
    if (complex_output)
        print_syscall(sys_code, regs, child);
    else
        print_simple_syscall(regs);
    if (sys_code != 60 && sys_code != 231) {
        if (resume_process(child, status) == 1)
            return (1);
        if (ptrace(PTRACE_GETREGS, child, NULL, regs) == -1)
            return (1);
    }
    display_return_value(sys_code, regs, complex_output);
    end_of_execution(sys_code);
    return (0);
}

int	register_extractor(struct user_regs_struct *regs,
pid_t child, int *status, int complex_output)
{
    long next_instruction = 0;

    next_instruction = ptrace(PTRACE_PEEKDATA, child, regs->rip, NULL);
    if (next_instruction == -1)
        return (1);
    next_instruction &= 0xffff;
    if (next_instruction != syscall_code)
        return (0);
    if (syscall_manager(regs, child, status, complex_output) == 1)
        return (1);
    return (0);
}

int trace_program(pid_t pid, int complex_output)
{
    struct  user_regs_struct regs;
    int     status = 0;

    if (waitpid(pid, &status, 0) < 0)
        return (1);
    while (1) {
        if (ptrace(PTRACE_GETREGS, pid, NULL, &regs) == -1)
            return (1);
        if (register_extractor(&regs, pid, &status, complex_output) == 1)
	        return (1);
        resume_process(pid, &status);
    }
    printf("\n");
    return (1);
}