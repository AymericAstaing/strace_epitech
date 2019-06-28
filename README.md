# strace_epitech (TECH 2 2018-2019)

strace traces a program in real time and displays all of the system calls it executes in their order of appearance.
The goal of this projet is to develop an alternative to strace that implementing the following options:

- -p: force a specific PID instead of executing a command
- -s: display the detailled arguments (see below).

By default, custom strace must only display the arguments and return values in hexadecimal form.
If the system call has a void return value, display a question mark.
With -s option, the program must be as close as possible to the strace command on your system,
and therefore display the following:
• integers in decimal form,
• pointers on a character string in the form of a character string,
• detailed structures (value for each field).

to build:

       make / make re
      
to launch:

      ./strace [-s] [-p <pid>|<command>]
      
Aymeric Astaing - EPITECH PARIS PROMO 2022
