/*
** EPITECH PROJECT, 2018
** utils.s
** File description:
** utils fcts
*/

#include <string.h>
#include <sys/user.h>

int is_pointer(char *type)
{
    int str_end = strlen(type);

    if (type[str_end - 1] == '*' && strcmp(type, "char *") &&
    strcmp(type, "char **"))
        return (1);
    return (0);
}

int is_end(int syscode)
{
    return (syscode == 60 || syscode == 231);
}

unsigned long long int get_register_value(int arg_id,
struct user_regs_struct *regs)
{
    if (arg_id == -1)
        return (regs->rax);
    if (arg_id == 0)
        return (regs->rdi);
    if (arg_id == 1)
        return (regs->rsi);
    if (arg_id == 2)
        return (regs->rdx);
    if (arg_id == 3)
        return (regs->rcx);
    if (arg_id == 4)
        return (regs->r8);
    if (arg_id == 5)
        return (regs->r9);
    return (0);
}