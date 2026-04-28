*This project has been created as part of the 42 curriculum by hbray asauvage*

# Description

Minishell is a project that required building a minimalist shell in C. The main goal is to understand how process execution works, how to synchronize processes, how to properly redirect output to the correct file descriptors, and how to manage pipes.

### Brief

The overall flow of the program is to parse what the user types into tokens and then execute them correctly based on their syntax. We therefore need to emulate the behavior of `bash --posix
	-Lexical and Syntactic Analysis: Tokenizing user input and handling single (') and double (") quotes to control metacharacter interpretation
	
	-Process Management: Utilizing system calls (fork, execve, waitpid) to spawn and manage child processes for command execution.

	-Inter-Process Communication (IPC): Implementing pipelines (|) to route the standard output of one command to the standard input of the next.

	-File Redirections: Manipulating file descriptors (using dup2) to handle input/output redirections (<, >, <<, >>).

	-Environment Management: Storing, fetching, and expanding environment variables (e.g., $USER, $?).

	-Signal Handling: Intercepting and managing asynchronous signals (like Ctrl+C and Ctrl+\) to prevent abrupt termination of the main shell loop.

# Instruction

### Compilation

The project uses a Makefile to automate the compilation process. Navigate to the root directory of the repository and run the following command to compile the source code into an executable:

-make: Compiles the project and generates the minishell executable
```bash
	make
```
-make clean: Deletes all intermediate object files (.o), keeping the executable.
```bash
	make clean
```
-make fclean: Executes clean and also deletes the minishell executable.
```bash
	make fclean
```
-make re: Executes fclean followed by all to force a complete recompilation.
```bash
	make re
```

### Execution

-Once compiled, you can launch the interactive shell by executing the generated binary:
```bash
	./minishell
```
To exit the shell, type exit or use the Ctrl+D shortcut (EOF).

# Resources

### References & Documentation

The development of this minishell relied heavily on the following foundational resources to understand Unix system programming and shell architecture:

-[AST] (https://en.wikipedia.org/wiki/Abstract_syntax_tree) (Abstract Syntax Tree) Concepts: Used to design the parser logic, ensuring commands, pipes, and redirections are evaluated in the correct order of precedence.

-[Bash Features] (https://www.gnu.org/software/bash/manual/bash.html#Shell-Syntax)

-[Doc SHELL] (https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html) 

-Linux Man Pages: The primary source of truth for all allowed system calls (man 2 fork, man 2 pipe, man 3 execve, man 2 dup2, man 3 tcsetattr).

### AI Usage

Artificial Intelligence tools were utilized during the development of this project strictly as a learning assistant and documentation aid. Specifically, AI was used for:

    Documentation: Drafting and structuring the content of this README.md file.

    Algorithmic Practice: Generating isolated recursion exercises to train for the conceptualization and implementation of the Abstract Syntax Tree (AST).

    Theoretical Comprehension: Explaining the underlying mechanics and expected behaviors of specific C library functions and Unix system calls.

    Debugging Analysis: Helping to understand the root causes of complex bugs and error messages (such as segmentation faults or unexpected process behaviors) encountered during execution.
