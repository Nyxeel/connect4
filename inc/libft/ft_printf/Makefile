NAME := printf.a
HEADER := ft_printf.h

CC := cc
CFLAGS := -Wall -Wextra -Werror

SRC := \
	ft_printf.c \
	va_start.c \
	find_arg.c \
	print_base.c \
	print_str.c


OBJ := $(SRC:.c=.o)
RM := rm -f

%.o: %.c $(HEADER)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	@ar rcs $(NAME) $(OBJ)

all: $(NAME)

clean:
	@$(RM) $(OBJ)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

