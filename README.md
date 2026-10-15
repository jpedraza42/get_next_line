*This project has been created as part of the 42 Málaga Fundación Telefónica curriculum by jpedraza.*

# get_next_line

## Description

**get_next_line** is a 42 Málaga Fundación Telefónica curriculum project whose goal is to implement a function capable of reading a file line by line using only low-level system calls and manual dynamic memory management.

The implemented function:

```c
char	*get_next_line(int fd);
```

returns a complete line on each call, including the newline character (`\n`) when present. When the end of the file is reached, the function returns the last remaining line and subsequently returns `NULL`.

This project introduces fundamental concepts of systems programming in C:

* File descriptors (`fd`)
* System calls (`read`)
* Dynamic memory management (`malloc` and `free`)
* Static variables
* String manipulation
* Memory leak prevention

---

## Objective

Implement a function capable of:

1. Reading from any valid file descriptor.
2. Returning exactly one line per call.
3. Preserving the reading state between consecutive calls.
4. Handling files of any size correctly.
5. Working with any `BUFFER_SIZE` value.
6. Avoiding memory leaks and invalid memory accesses.

---

## Selected Algorithm

### Problem

The `read()` function does not necessarily return a complete line. Depending on the value of `BUFFER_SIZE`, it may return:

```text
Hello
```

or

```text
He
```

Therefore, it is necessary to temporarily store the data read until a complete line can be returned.

### Solution

A static variable is used:

```c
static char	*store;
```

which preserves any unread content between function calls.

### General Workflow

#### 1. Read and Accumulate

As long as no newline character (`\n`) exists in the accumulated content:

```text
store
```

the function continues performing calls to:

```c
read(fd, buffer, BUFFER_SIZE);
```

The newly read data is concatenated to `store`.

#### 2. Extract the Line

Once a newline character is found or the end of the file is reached:

```text
Hello\nWorld
```

the function extracts:

```text
Hello\n
```

which will be returned to the caller.

#### 3. Save the Remaining Content

The remaining content:

```text
World
```

is stored again in:

```text
store
```

to be processed during the next call.

#### 4. Free Memory

All temporary memory used during the process is properly released to prevent memory leaks.

---

## Project Structure

```text
.
├── get_next_line.c
├── get_next_line_utils.c
├── get_next_line.h
└── README.md
```

### get_next_line.c

Contains:

* `get_next_line`
* `ft_read_and_store`

### get_next_line_utils.c

Contains helper functions:

* `ft_strlen`
* `ft_str_end_line`
* `ft_strjoin`
* `ft_extract_line`
* `ft_extract_rest`

### get_next_line.h

Contains:

* Required includes
* `BUFFER_SIZE` definition
* Function prototypes

---

## Instructions

### Compilation

Compile the source files:

```bash
cc -Wall -Wextra -Werror -c get_next_line.c get_next_line_utils.c
```

### Test Example

```bash
cc -Wall -Wextra -Werror main.c get_next_line.c get_next_line_utils.c
```

### Execution

```bash
./a.out
```

### Compilation with a Custom BUFFER_SIZE

```bash
cc -Wall -Wextra -Werror \
-D BUFFER_SIZE=42 \
main.c get_next_line.c get_next_line_utils.c
```

---

## Usage Example

```c
int		fd;
char	*line;

fd = open("text.txt", O_RDONLY);

line = get_next_line(fd);
while (line)
{
	printf("%s", line);
	free(line);
	line = get_next_line(fd);
}
close(fd);
```

---

## Validation

The project has been verified using:

### Norminette

```bash
norminette
```

### Compilation

```bash
cc -Wall -Wextra -Werror
```

### Valgrind

```bash
valgrind --leak-check=full ./a.out
```

Result:

```text
All heap blocks were freed -- no leaks are possible
ERROR SUMMARY: 0 errors
```

---

## Resources

### Official Documentation

* `read(2)` manual
* `open(2)` manual
* `malloc(3)` manual
* `free(3)` manual
* `close(2)` manual

Available through:

```bash
man read
man open
man malloc
man free
man close
```

---

## Use of Artificial Intelligence

During the development of this project, AI was used exclusively as an educational support tool for:

* Understanding how `read()` works.
* Understanding the purpose and behavior of `BUFFER_SIZE`.
* Assisting in the preparation of this README file.

---

## Key Learnings

This project provides a deeper understanding of:

* Incremental file reading.
* Data persistence through static variables.
* Safe dynamic memory management.
* Stream-oriented algorithm design.
* Buffer handling and Unix input/output operations.

## Bonus Part

After completing the mandatory part, an additional version of the project was implemented to support multiple file descriptors simultaneously.

### Objective

The goal of the bonus part is to allow `get_next_line()` to maintain an independent reading state for each file descriptor.

This means that different files can be read alternately without losing track of the current position in any of them.

Example:

```c
get_next_line(fd1);
get_next_line(fd2);
get_next_line(fd3);
get_next_line(fd1);
get_next_line(fd2);
get_next_line(fd3);
```

Each file descriptor continues reading from the exact position where it stopped during the previous call.

---

### Algorithm

The mandatory version uses a single static variable:

```c
static char *store;
```

The bonus version replaces it with an array of static pointers:

```c
static char *store[1024];
```

Each file descriptor has its own storage area:

```text
store[3]
store[4]
store[5]
...
```

This allows the function to preserve independent reading states for multiple files at the same time.

The helper functions remain unchanged, and only the management of the static storage is modified.

---

### Bonus Files

The bonus implementation is provided in the following files:

```text
get_next_line_bonus.c
get_next_line_bonus.h
get_next_line_utils_bonus.c
```

---

### Bonus Example

Assume the following files:

File 1:

```text
A1
A2
A3
```

File 2:

```text
B1
B2
B3
```

The following sequence:

```c
get_next_line(fd1);
get_next_line(fd2);
get_next_line(fd1);
get_next_line(fd2);
```

returns:

```text
A1
B1
A2
B2
```

demonstrating that each descriptor preserves its own reading position independently.

---

### Bonus Validation

The bonus implementation was tested using:

* Multiple file descriptors opened simultaneously.
* Different BUFFER_SIZE values.
* Valgrind memory analysis.
* Norminette verification.

Result:

```text
All heap blocks were freed -- no leaks are possible
ERROR SUMMARY: 0 errors
```
