# 🖨️ ft_printf

*This project has been created as part of the 42 curriculum by pjelinek*

---

## 🧠 Description

The objective of this project is to re-implement the standard C function **printf**.

`ft_printf` reproduces formatted output to the standard output using a subset of the original printf functionality.
It focuses on variadic functions, format parsing, and controlled output without relying on the original libc implementation.

Core learning goals of the project:

* Understanding **variadic arguments** (`va_list`, `va_start`, `va_arg`, `va_end`)
* Parsing format strings
* Handling different data types and conversions
* Managing output and return values
* Writing modular, reusable C code

The implementation emphasizes clarity, correctness, and handling of edge cases.

---

## ⚙️ Compilation

Compile the project using:

```bash
make
```

Clean object files:

```bash
make clean
```

Remove all build artifacts:

```bash
make fclean
```

Rebuild from scratch:

```bash
make re
```

---

## 🔌 Usage

Include the header in your project:

```c
#include "ft_printf.h"
```

Compile with the library:

```bash
cc main.c libftprintf.a
```

Example usage:

```c
ft_printf("Hello %s!\n", "world");
```

---

## 🧩 Supported Conversions

The implementation supports the most common format specifiers:

* `%c` — character
* `%s` — string
* `%p` — pointer address
* `%d` — decimal integer
* `%i` — integer
* `%u` — unsigned integer
* `%x` — hexadecimal (lowercase)
* `%X` — hexadecimal (uppercase)
* `%%` — percent symbol

---

## 📁 Project Structure

```
ft_printf/
│
├── ft_printf.c        # main printf logic
├── ft_printf.h        # header file & prototypes
├── find_arg.c         # argument parsing and dispatch
├── print_base.c       # number printing in different bases
├── print_str.c        # string and character output helpers
├── va_start.c         # variadic argument handling utilities
└── Makefile           # build rules
```

---

## 🔍 Implementation Notes

* Uses **variadic functions** to process a variable number of arguments.
* Format string is parsed character by character.
* Each conversion is delegated to a dedicated function.
* Output is written directly to file descriptor `1` (stdout).
* Return value matches the behavior of the original `printf`
  (number of printed characters).

---

## 📎 Resources

* `man printf`
* `man stdarg`
* 42 ft_printf subject (official project PDF on the intra)
* C standard documentation on formatted output

---

## 🤖 Note

AI was used for the exploratory part of this project
(conceptual understanding, parsing strategies, edge-case considerations, etc.)

