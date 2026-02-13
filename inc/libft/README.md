# 📚 libft

*This project has been created as part of the 42 curriculum by pjelinek*

---

## 🧠 Description

The objective of this project is to implement **libft**: your own C library that re-creates common standard functions and adds a set of useful utilities you will re-use across many 42 projects.

### The library includes

* **Character checks & conversions** (`ft_is*`, `ft_to*`)
* **String handling** (length, copy, join, trim, split, search, compare, etc.)
* **Memory handling** (set, copy, move, compare, zeroing, allocation)
* **Conversions** (ASCII ↔ integers, `itoa`, overflow checks)
* **File descriptor output helpers** (`*_fd`)
* **Linked list utilities** (**bonus**)
* **get_next_line** (line-by-line file reading)

**Goal:** not just working code, but **clean C**, consistent behavior, careful edge-case handling, and solid memory management.

---

## ⚙️ Instructions

### Compile the library

```bash
make
```

### Compile with bonus functions

```bash
make bonus
```

### Clean build files

```bash
make clean
```

### Full clean (objects + library)

```bash
make fclean
```

### Rebuild from scratch

```bash
make re
```

---

## 🔌 Usage in another project

Include the header:

```c
#include "libft.h"
```

---

## 🧩 Included Functions

### 🔤 Character checks & conversion

```
ft_isalnum
ft_isalpha
ft_isascii
ft_isdigit
ft_isprint
ft_isspace
ft_tolower
ft_toupper
```

### 🧵 String utilities

```
ft_strlen
ft_strlcpy
ft_strlcat
ft_strncmp
ft_strchr
ft_strrchr
ft_strcpy
ft_strncpy
ft_strnstr
ft_strdup
ft_strjoin
ft_strtrim
ft_strmapi
ft_striteri
ft_substr
ft_split
ft_strcmp
ft_strcat
ft_wordcount
```

### 🧠 Memory utilities

```
ft_memset
ft_memcpy
ft_memmove
ft_memchr
ft_memcmp
ft_bzero
ft_calloc
```

### 🔢 Conversions & parsing helpers

```
ft_atoi
ft_atoll
ft_itoa
```

#### Helpers for robust parsing

```
ft_skip_whitespaces
ft_skip_signs
ft_skip_zeros
int_overflow_check
ll_overflow_check
```

### 🖨️ Output to file descriptors

```
ft_putchar_fd
ft_putstr_fd
ft_putendl_fd
ft_putnbr_fd
```

### 🔗 Linked list utilities (bonus)

```
ft_lstnew_bonus
ft_lstadd_front_bonus
ft_lstadd_back_bonus
ft_lstdelone_bonus
ft_lstclear_bonus
ft_lstiter_bonus
ft_lstlast_bonus
ft_lstmap_bonus
ft_lstsize_bonus
```

### 📄 get_next_line

```
gnl/get_next_line
```

---

## 📎 Resources

* 42 libft subject (official project PDF on the intra)
* Manual pages for C standard library functions
  (`man strlen`, `man memcpy`, …)

---

## 🤖 Note

AI was used for the exploratory part of this project
(conceptual understanding, edge-case brainstorming, etc.)

