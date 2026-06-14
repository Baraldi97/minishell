*This project was created as part of the 42 curriculum by rcosta, bdavid-b.*

# Minishell

## Description

Minishell is a simplified implementation of a shell, inspired by the behavior
of **bash**. The goal of the project is to understand how a command-line
interpreter works internally: reading the user's input, performing lexical and
syntactic analysis of commands, expanding variables, handling quotes,
redirections, pipes, and executing processes.

The program displays an interactive prompt, reads the commands typed by the
user, and executes them, replicating the expected behavior of a real shell.
Among the supported features are:

- Execution of commands using their absolute/relative path or through the
  `PATH` environment variable.
- Single (`'`) and double (`"`) quotes with proper handling of metacharacters.
- Expansion of environment variables (`$VAR`) and the exit status of the last
  command (`$?`).
- Input and output redirections (`<`, `>`, `>>`) and *heredocs* (`<<`).
- Chaining of commands through *pipes* (`|`).
- Built-in commands: `echo`, `cd`, `pwd`, `export`, `unset`, `env`, and `exit`.
- Signal handling (`Ctrl-C`, `Ctrl-D`, `Ctrl-\`).

## Instructions

### Compilation

The project uses a `Makefile`. To compile, run the following from the root of
the repository:

```bash
make
```

This generates the `minishell` executable. The internal libraries (`libft` and
`printf`) are compiled automatically.

Rules available in the `Makefile`:

| Rule         | Description                                              |
|--------------|----------------------------------------------------------|
| `make`       | Compiles the project and generates the `minishell` binary. |
| `make clean` | Removes the object files (`.o`).                         |
| `make fclean`| Removes the object files and the executable.            |
| `make re`    | Rebuilds the project from scratch (`fclean` + `make`).   |

> **Dependency:** the project depends on the **readline** library. On
> Debian/Ubuntu-based systems, install it with
> `sudo apt-get install libreadline-dev`.

### Usage

After compiling, start the shell with:

```bash
./minishell
```

A prompt will be displayed. Type commands as you would in a normal shell. To
end the session, use the `exit` built-in or press `Ctrl-D`.

## Resources

The references below were used during the development of the project:

- **[GNU Bash Reference Manual](https://www.gnu.org/software/bash/manual/bash.html)**
  — the official bash documentation. Used as the main reference to define the
  expected behavior of the shell: variable expansion rules, quote handling, and
  the behavior of the built-ins.

- **[GNU Readline Library](https://tiswww.case.edu/php/chet/readline/rltop.html)**
  — documentation for the `readline` library. Consulted for reading the user's
  input, managing history, and the interactive prompt (`readline`,
  `add_history`).

- **System `man` pages** (`man fork`, `man execve`, `man pipe`, `man dup2`,
  `man wait`, `man signal`) — reference for the **execution** part: process
  creation, process image replacement, communication through *pipes*,
  redirections, and signal handling.

- **[42 Docs / Norm](https://github.com/42School/norminette)** — used to ensure
  that the code follows the 42 *Norm*, applicable to every part of the project.
