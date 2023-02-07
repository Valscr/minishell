# minishell

A basic shell written in C

Features
- Handles pipes (|)
- Handles redirection (>, <, >> and <<)
- Handles command history (using up and down arrow keys)
- Handles environment variables
- Handles keyboard interrupt signals such as Ctrl-C, Ctrl-D, and Ctrl-\

Built-in commands:
- cd
- echo with -n option
- env
- pwd
- unset
- export
- exit

Compiling the program
To compile the program, use make:

```make```

Running the program
To run the program, use ./minishell:

```./minishell```

To run with valgrind without readline leaks :

```valgrind --suppressions=valgrind_readline ./minishell```
