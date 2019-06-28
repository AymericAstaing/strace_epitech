##
## EPITECH PROJECT, 2017
## Makefile
## File description:
## PSU_strace_2018
##

CFLAGS  +=      -Wall -Werror -Wextra
CFLAGS  +=      -I./include

SRC     +=      ./src/main.c				\
				./src/print_syscall.c		\
				./src/print_simple_syscall.c\
				./src/utils.c				\
				./src/signal_error_handler.c\
				./src/print_type.c			\
				./src/print_type2.c			\
				./src/trace.c

NAME    =       strace

all:            $(NAME)

$(NAME):
	gcc -o $(NAME) $(SRC) $(CFLAGS)

clean:
	rm -f $(NAME)

fclean: clean
	rm -f $(NAME)

re:     fclean all

.PHONY: clean fclean re all
