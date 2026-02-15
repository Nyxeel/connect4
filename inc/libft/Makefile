# =========================================
# libft/Makefile — libft + ft_printf → libft.a
# =========================================

NAME            := libft.a

# Compiler & Flags (42)
CC              := cc
CFLAGS          := -Wall -Wextra -Werror

# Libft-Header
HEADER          := libft.h

# ft_printf (eigener Ordner mit eigener Makefile)
FT_PRINTF_DIR   := ft_printf
FT_PRINTF_A     := $(FT_PRINTF_DIR)/printf.a

# Temp-Ordner zum Entpacken der printf-Objekte
TMP_DIR         := .printf_objs

# Werkzeuge
AR              := ar rcs
RM              := rm -f
RMDIR           := rm -rf
MKDIR           := mkdir -p

# -----------------------------------------
# Libft-Quellen (deine Liste unverändert)
# -----------------------------------------
SRC := \
	src/ft_isalnum.c \
	src/ft_isalpha.c \
	src/ft_isascii.c \
	src/ft_isdigit.c \
	src/ft_isprint.c \
	src/ft_tolower.c \
	src/ft_toupper.c \
	src/ft_split.c \
	src/ft_strlen.c \
	src/ft_strlcpy.c \
	src/ft_strlcat.c \
	src/ft_strncmp.c \
	src/ft_strchr.c \
	src/ft_strrchr.c \
	src/ft_strcpy.c \
	src/ft_strncpy.c \
	src/ft_strnstr.c \
	src/ft_strdup.c \
	src/ft_strjoin.c \
	src/ft_strtrim.c \
	src/ft_strmapi.c \
	src/ft_striteri.c \
	src/ft_substr.c \
	src/ft_memset.c \
	src/ft_memcpy.c \
	src/ft_memmove.c \
	src/ft_memchr.c \
	src/ft_memcmp.c \
	src/ft_bzero.c \
	src/ft_calloc.c \
	src/ft_atoi.c \
	src/ft_itoa.c \
	src/ft_skip_zeros.c \
	src/ft_strcmp.c \
	src/ft_atoll.c \
	src/ft_putchar_fd.c \
	src/ft_putstr_fd.c \
	src/ft_putendl_fd.c \
	src/ft_isspace.c \
	src/ft_wordcount.c \
	src/ft_putnbr_fd.c \
	src/ft_lstnew_bonus.c \
	src/ft_skip_whitespaces.c \
	src/ft_skip_signs.c \
	src/ll_overflow_check.c \
	src/int_overflow_check.c \
	src/ft_lstadd_front_bonus.c \
	src/ft_lstadd_back_bonus.c \
	src/ft_lstdelone_bonus.c \
	src/ft_lstclear_bonus.c \
	src/ft_lstiter_bonus.c \
	src/ft_lstlast_bonus.c \
	src/ft_strcat.c \
	src/ft_lstmap_bonus.c \
	src/ft_lstsize_bonus.c \
	get_next_line/get_next_line.c \

OBJ := $(SRC:.c=.o)

# -----------------------------------------
# Targets
# -----------------------------------------

all: $(NAME)

# 1) Baue libft-Objekte → libft.a
# 2) Baue ft_printf (eigene Makefile)
# 3) Extrahiere alle .o aus libftprintf.a und füge sie in libft.a ein
$(NAME): $(OBJ)
	@$(AR) $(NAME) $(OBJ)
	@$(MAKE) -C $(FT_PRINTF_DIR)
	@$(MKDIR) $(TMP_DIR)
	@cd $(TMP_DIR) && ar -x ../$(FT_PRINTF_A)
	@$(AR) $(NAME) $(TMP_DIR)/*.o
	@$(RMDIR) $(TMP_DIR)

# Generische Regel für .c → .o
%.o: %.c $(HEADER)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJ)
	@$(MAKE) -C $(FT_PRINTF_DIR) clean
	@$(RMDIR) $(TMP_DIR)

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C $(FT_PRINTF_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
