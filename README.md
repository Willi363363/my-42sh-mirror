# 42sh - Custom Unix Shell Implementation

> **Epitech First Year Project** | A feature-rich Unix shell developed in C by a team of 4 students

---

## 📌 About the Project

**42sh** is a custom Unix shell implementation developed as part of the Epitech first-year curriculum. This project was created by me and three teammates, and demonstrates our understanding of shell mechanics, process management, and system programming in C.

The shell provides a complete command-line interface with numerous built-in commands and advanced features that rival standard Unix shells like bash or zsh.

---

## ✨ Features

### Core Shell Functionality
- **Command Execution**: Execute any system binary or script from your PATH
- **Prompt Display**: Interactive prompt with current working directory and exit status color coding (red for failure, green for success)
- **Input Handling**: Read and parse user input with proper line buffering
- **Environment Management**: Full environment variable support inherited from parent process

### Built-in Commands

#### Environment Management
| Command | Description |
|---------|-------------|
| `setenv VAR VALUE` | Set an environment variable |
| `unsetenv VAR` | Remove an environment variable |

#### Navigation & Path
| Command | Description |
|---------|-------------|
| `cd [path]` | Change directory (supports `~`, `-`, relative and absolute paths) |

#### Command Information
| Command | Description |
|---------|-------------|
| `which cmd` | Show the full path of shell commands |
| `where cmd` | Display all locations of a command in PATH |

#### Shell Customization
| Command | Description |
|---------|-------------|
| `alias name='command'` | Create command aliases |
| `unalias name` | Remove an alias |
| `alias` | List all defined aliases |

#### History Management
| Command | Description |
|---------|-------------|
| `history` | Display command history |
| `!!` | Execute the last command |
| `!n` | Execute command number n from history |

#### Advanced Features
| Command | Description |
|---------|-------------|
| `repeat n cmd` | Execute a command n times |

### Advanced Shell Features

#### Command Parsing & Execution
- **Tokenization**: Advanced lexer that handles:
  - Command words and arguments
  - Environment variable expansion (`$VAR`, `${VAR}`)
  - Pipe operators (`\|`)
  - Logical operators (`&&`, `||`)
  - Command separators (`;`)
  - Parentheses for subshells `(command)`

- **Redirections**: Full support for input/output redirection:
  - Input redirection (`< file`)
  - Output redirection (`> file`)
  - Append redirection (`>> file`)
  - Here-document (`<< EOF` ... `EOF`)

- **Pipe Support**: Chain commands together with `\[cmd1] | [cmd2] | [cmd3]`

- **Logical Operators**:
  - `cmd1 && cmd2` - Execute cmd2 only if cmd1 succeeds
  - `cmd1 || cmd2` - Execute cmd2 only if cmd1 fails

- **Command Sequencing**: Execute multiple commands sequentially with `;`

- **Subshells**: Execute commands in a subshell using parentheses `(command)`

#### Code Editor Mode
The shell includes a built-in code editor mode for enhanced command editing experience with ncurses library support.

---

## 🚀 Getting Started

### Prerequisites
- A Unix-like operating system (Linux, macOS)
- GCC or compatible C compiler
- Make (GNU Make recommended)
- ncurses library
- criterion library (for tests)

### Installation

1. **Clone the repository:**
   ```bash
   git clone https://github.com/your-username/42sh.git
   cd 42sh
   ```

2. **Compile the shell:**
   ```bash
   make
   ```

3. **Run the shell:**
   ```bash
   ./42sh
   ```

### Usage Examples

#### Basic Usage
```bash
# Start the shell
./42sh

# Execute commands
$ ls -la
$ echo "Hello, World!"

# Use built-in commands
$ cd /tmp
$ setenv MY_VAR "my value"
$ echo $MY_VAR
my value

# Exit the shell
$ exit
```

#### Advanced Usage
```bash
# Pipe commands
$ cat file.txt | grep "pattern" | wc -l

# Logical operators
$ make && ./my_program
$ test -f file.txt || echo "File not found"

# Redirections
$ ls -la > output.txt
$ cat input.txt | grep "error" >> errors.log

# Here-document
$ cat << EOF
> This is a multi-line
> input using heredoc
> EOF

# Subshells
$ (cd /tmp && ls) || echo "Failed"

# Command repetition
$ repeat 5 echo "Hello"

# Aliases
$ alias ll='ls -la'
$ ll

# Command history
$ history
$ !!  # Re-execute last command
```

---

## 📁 Project Structure

```
42sh/
├── include/                    # Header files
│   ├── global.h                # Global definitions and constants
│   ├── shell.h                 # Shell parameters and main structures
│   ├── alias.h                 # Alias management
│   ├── env.h                   # Environment variables handling
│   ├── history.h               # Command history
│   ├── lexer.h                 # Lexical analysis
│   ├── parsing.h               # AST parsing
│   ├── execution.h             # Command execution
│   ├── cod_editor.h            # Code editor mode
│   └── builtins/               # Built-in commands headers
│       ├── env.h               # Environment builtins
│       └── misc.h              # Miscellaneous builtins
│
├── src/                       # Source files
│   ├── main.c                  # Program entry point
│   ├── my_42sh.c               # Main shell loop
│   ├── shell/                  # Shell core functionality
│   ├── lexer/                  # Lexer implementation
│   ├── parsing/                # Parser implementation
│   ├── execution/              # Execution engine
│   ├── builtins/               # Built-in commands
│   │   ├── env/                # Environment builtins
│   │   └── misc/               # Miscellaneous builtins
│   ├── alias/                  # Alias management
│   ├── history/                # Command history
│   ├── env/                    # Environment handling
│   ├── expansion/              # Variable expansion
│   └── utils/                  # Utility functions
│
├── tests/                      # Unit tests
│   ├── builtins/               # Built-in tests
│   ├── execution/              # Execution tests
│   ├── lexer/                  # Lexer tests
│   └── parsing/                # Parser tests
│
├── Makefile                    # Build system
└── README.md                   # This file
```

---

## 🔧 Build Options

| Target | Description |
|--------|-------------|
| `make` or `make all` | Build the shell |
| `make debug` | Build with debug symbols |
| `make clean` | Remove object files |
| `make fclean` | Remove all build artifacts |
| `make re` | Clean and rebuild |
| `make tests_run` | Compile and run unit tests |
| `make tests_show` | Run tests with coverage report |
| `make sanity_check` | Run static analysis with scan-build |

---

## 🛠️ Technical Details

### Architecture Overview

```
Input → Lexer → Parser → AST → Executor → Output
```

1. **Lexer**: Tokenizes input into meaningful units (words, operators, etc.)
2. **Parser**: Builds an Abstract Syntax Tree (AST) from tokens
3. **Executor**: Walks the AST and executes commands with proper redirections and process management

### Supported Token Types
- Words and environment variables
- Pipe (`\|`)
- Logical AND (`&&`)
- Logical OR (`||`)
- Semicolon (`;`)
- Input redirection (`<`)
- Here-document (`<<`)
- Output redirection (`>`)
- Append redirection (`>>`)
- Parentheses (`(`, `)`)

### Supported AST Node Types
- Simple commands
- Pipes
- Logical AND/OR operations
- Command sequences
- Subshells
- All redirection types

---

## 🎓 Learning Outcomes

This project allowed us to:
- Master C programming and memory management
- Understand Unix system calls and process management
- Implement complex parsing and lexical analysis
- Work with file descriptors and I/O redirection
- Develop a modular and maintainable codebase
- Collaborate effectively in a team of 4 developers
- Apply Epitech's coding standards and best practices

---

## 📜 License

This project was developed as part of the Epitech curriculum and is provided as-is. Feel free to use it for educational purposes.

---

## 👥 Team Members

- **Me** - [GitHub Profile](https://github.com/Willi363363)
- **Ismael** - [Github Profile](https://github.com/geod-dev)
- **Yael** - [Github Profile](https://github.com/Yael-pie)
- * **Guilhem** - [Github Profile](https://github.com/guilhemcg)

---

## 🏆 Achievements

- Full shell implementation with all required features
- Advanced features: pipes, redirections, logical operators
- Comprehensive built-in commands
- Command history with file persistence
- Alias system
- Command repetition
- Subshell support
- Color-coded prompt
- Here-document support
- Complete test suite

---

## 💡 Usage Tips

1. **Customize your prompt**: The prompt automatically shows the current directory and changes color based on the exit status of the previous command.

2. **Use aliases for frequently used commands**:
   ```bash
   alias gs='git status'
   alias ga='git add .'
   alias gc='git commit -m'
   ```

3. **Chain commands efficiently**:
   ```bash
   make && ./program || echo "Build failed"
   ```

4. **Use history to repeat commands**:
   ```bash
   history       # View history
   !!           # Repeat last command
   !5           # Execute command #5 from history
   ```

5. **Test scripts with subshells**:
   ```bash
   (cd /tmp && rm -rf test_dir)  # Changes don't affect current shell
   ```

---

*Developed at Epitech during the first year. Special thanks to our peers and teachers for their guidance.*
