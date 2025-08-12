# Mini_HELL: A Custom UNIX Shell

![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)
![42 School](https://img.shields.io/badge/42%20Project-black?style=for-the-badge&logo=42)
![ 1337 School ](https://img.shields.io/badge/1337%20Project-black?style=for-the-badge&logo=1337)
![Minishell](https://img.shields.io/badge/Minishell-000000?style=for-the-badge&logo=terminal&logoColor=white)

## Overview

**Mini_HELL** is a custom UNIX shell implementation, created as a core project for the 42 Network curriculum (at 1337 School). The goal is to create a light, functional command-line interpreter that replicates a subset of the features found in standard shells like `bash`.

This project dives deep into process management, file descriptors, signal handling, and parsing in C. It's a comprehensive exercise in understanding how the shell, a fundamental part of the UNIX operating system, works under the hood.

## Table of Contents
- [How a Shell Processes a Command](#how-a-shell-processes-a-command)
- [Key Features](#key-features)
- [Project Structure](#project-structure)
- [Getting Started](#getting-started)
- [License](#license)
- [Acknowledgments](#acknowledgments)

***

## How a Shell Processes a Command

A shell's primary job is to read a command, parse it, and execute it. The process can be visualized as a pipeline. For a command like `cat file.txt | grep "hello" > output.txt`, the flow looks like this:

```
[ Start: Prompt & Read Line ]
              |
              v
[ Parse & Build Command Structure ]
              |
              v
[ Executor for `cat file.txt | grep 'hello' > out.txt` ]
  |
  +-> [ Parent Process ] -- forks --> [ Child 1: `cat` ]
  |     |                            | - stdin:  file.txt
  |     |                            | - stdout: pipe write-end
  |     |                            +-> execve('cat')
  |     |
  |     +----------- forks --> [ Child 2: `grep` ]
  |                                  | - stdin:  pipe read-end
  |                                  | - stdout: out.txt
  |                                  +-> execve('grep')
  |
  +-> [ Parent waits for all children ]
              |
              v
[ Display new prompt & Loop ]
```

***

## Key Features

This minishell aims to replicate essential `bash` functionalities:

* **Command Execution:** Finds and executes commands from the `PATH`.
* **Built-in Commands:** Implements a set of commands directly within the shell:
  * `echo` with the `-n` option.
  * `cd` with relative and absolute paths.
  * `pwd` to display the current working directory.
  * `export` to manage environment variables.
  * `unset` to remove environment variables.
  * `env` to display the environment variables.
  * `exit` to terminate the shell.
* **Pipes (`|`):** Chains commands together, piping the output of one command to the input of the next.
* **Redirections:**
  * `<`: Redirects standard input.
  * `>`: Redirects standard output.
  * `<<`: "Here document" for input.
  * `>>`: Appends to a file.
* **Environment Variables:** Expands variables prefixed with `$` (e.g., `$USER`).
* **Signal Handling:**
  * `Ctrl-C`: Displays a new prompt without quitting.
  * `Ctrl-D`: Exits the shell.
  * `Ctrl-\`: Does nothing.

***

## Project Structure

A typical structure for a `minishell` project at 42:

```
Mini_HELL/
├── Makefile
├── include/
│   └── minishell.h      # Main project header
├── libft/                 # Custom C library
├── src/
│   ├── main.c
│   ├── parsing/
│   ├── execution/
│   └── builtins/
└── README.md
```

* `Makefile`: Compiles the project.
* `include/`: Contains header files.
* `libft/`: The student's custom C library, a prerequisite for most 42 projects.
* `src/`: The source code, often organized by functionality (parsing, execution, built-ins).

***

## Getting Started

### Prerequisites

* A C compiler (e.g., `cc`, `gcc`, or `clang`)
* `make` utility
* Readline library (often required or bonus)

### Installation & Compilation

1. **Clone the repository:**
   ```bash
   git clone [https://github.com/achahid19/Mini_HELL.git](https://github.com/achahid19/Mini_HELL.git)
   cd Mini_HELL
   ```

2. **Compile the project:**
   A `Makefile` is standard for 42 projects. Simply run `make`.
   ```bash
   make
   ```
   This will create the `minishell` executable.

3. **Run the shell:**
   ```bash
   ./minishell
   ```

### Example Usage

Once running, you can try commands like:

```sh
# Simple command
> ls -l

# Using a pipe
> cat /dev/random | head -c 100

# Environment variables
> echo "Hello, $USER"

# Redirection
> ls > file_list.txt

# Built-in command
> cd .. && pwd
```

***

## 📜 License

This project is typically not licensed for redistribution, as it is academic work. Please respect the 42 Network's academic integrity policies.



## Author
**© Anas Chahid ksabi **@KsDev**** - [achahid19](https://github.com/achahid19)

## Acknowledgements
This project is part of the curriculum at **1337 Coding School**, a member of the **42 Network**. It represents a significant challenge and a major learning milestone in the program.

[![School](https://img.shields.io/badge/Notice-1337%20School-blue.svg)](https://1337.ma/en/)
[![School](https://img.shields.io/badge/Notice-42%20School-blue.svg)](https://42.fr/en/homepage/)
