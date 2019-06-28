/*
** EPITECH PROJECT, 2018
** bttf main.c
** File description:
** main.c
*/

#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ptrace.h>
#include "../include/strace.h"


int attach_to_child(int argc, char **argv)
{
    char *args[argc + 1];
    memcpy(args, argv, sizeof(char *) * argc);
    args[argc] = '\0';

    ptrace(PTRACE_TRACEME, 0, NULL, NULL);
    kill(getpid(), SIGSTOP);
    execvp(args[0], args);
    return (1);
}

static int trace_process_id(char **av, int complex)
{
    pid_t pid = atoi(av[2]);
    if (ptrace(PTRACE_ATTACH, pid, NULL, NULL) == -1)
        return (EXIT_KO);
    trace_program(pid, complex);
    return (0);
}

static int trace_cmd(int argc, char **argv, int complex)
{
    pid_t child = fork();
    int exe_path = 1;

    if (complex == 1)
        exe_path = 2;
    if (child == 0)
        return (attach_to_child(argc - exe_path, argv + exe_path));
    else
        return (trace_program(child, complex));
    return (0);
}

static int valid_args(int ac, char **av)
{
    int len = 0;
    if (ac < 2)
        return (TRACE_ERR);
    len = strlen(av[1]);
    if (strncmp(av[1], "--help", len) == 0) {
        fprintf(stderr, "USAGE: ./strace [-s] [-p <pid>|<command>]\n");
        return (TRACE_ERR);
    } else if (strncmp(av[1], "-p", len) == 0 && ac > 2)
        return (TRACE_PID);
    return(TRACE_CMD);
}

int main(int ac, char **av)
{
    int parser = valid_args(ac, av);
    int complex = 0;

    if (ac >= 2 && strcmp(av[1], "-s") == 0)
        complex = 1;
    if (parser == TRACE_ERR)
        return (EXIT_KO);
    else if (parser == TRACE_CMD)
        return (trace_cmd(ac, av, complex));
    else
        return (trace_process_id(av, complex));
}
