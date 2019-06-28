/*
** EPITECH PROJECT, 2018
** strace.h
** File description:
** strace.h
*/

#ifndef STRACE_H
#define STRACE_H

#include <sys/types.h>
#include <sys/user.h>

    static const int EXIT_OK = 0;
    static const int EXIT_KO = 1;
    
    static const int TRACE_ERR = 0;
    static const int TRACE_CMD = 1;
    static const int TRACE_PID = 2;
    static const int TRACE_COMPLEX = 3;

    static const int syscall_code = 0x050f;

    /************* trace.c *************/
    int trace_program(pid_t child, int complex_output);

    /************* syscall print (simple/complex) *************/
    void print_syscall(int syscode, struct user_regs_struct *regs, pid_t child);
    void print_simple_syscall(struct user_regs_struct *regs);
    void display_return_value(int syscode, struct user_regs_struct *regs, int complex);
    void print_syscall_name(int syscall_code);

    /************* special types print functions *************/
    void print_int(pid_t child, unsigned long long int register_value);
    void print_long(pid_t child, unsigned long long int register_value);
    void print_un_int(pid_t child, unsigned long long int register_value);
    void print_un_long(pid_t child, unsigned long long int register_value);
    void print_pointer(pid_t child, unsigned long long int register_value);
    void print_string(pid_t child, unsigned long long int register_value);
    void print_tab(pid_t child, unsigned long long int register_value);
    void print_not_implemented(pid_t child, unsigned long long int register_value);
    void do_nothing(pid_t child, unsigned long long int register_value);

    /************* utils *************/
    int is_pointer(char *type);
    int is_end(int syscode);
    unsigned long long int get_register_value(int arg_id, struct user_regs_struct *regs);


    typedef struct	s_syscall_params {
        char    *name;
        int     params_nbr;
        char    *params[6];
        char    *ret_type;
    } t_syscall_params;

    typedef struct	s_arg_type {
        char    *type;
        void    (*print_value)(pid_t pid, unsigned long long int ret_val);
    } t_arg_type;

#endif
