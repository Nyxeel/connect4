# =========================
# Project connct4
# =========================
NAME            = connect4
CC              = cc
CFLAGS          = -Wall -Werror -Wextra -MMD -MP
DEBUG_FLAGS     = -g -DVERBOSE=1


LDLIBS      = -lncurses

# =========================
# Libs / Includes
# =========================
LIBFT_DIR       = inc/libft
LIBFT           = $(LIBFT_DIR)/libft.a
INCLUDES        = -I inc -I $(LIBFT_DIR)

# =========================
# Folders
# =========================
SRC_DIR         = src
OBJ_DIR         = obj
OBJ_DIR_BONUS   = obj_bonus

# =========================
# Build-Mode
# =========================
MODE ?= mandatory

# =========================
# Sources (MANDATORY base)
# =========================
SRCS_MAND = \
	main.c \
	parse.c \
	init_game.c \
	start_game.c \
	signals.c \
	utils.c \
	cleanup.c \
	verbose.c \
	grid/render_grid.c


# =========================
# Bonus replacements/additions
# =========================

SRCS_BONUS_ONLY = \
	main_bonus.c \

SRCS_MAND_REPLACED = \
	main.c \


# =========================
# Mode selection
# =========================
ifeq ($(MODE),bonus)
  OBJDIR = $(OBJ_DIR_BONUS)
  SRCS   = $(filter-out $(SRCS_MAND_REPLACED),$(SRCS_MAND)) $(SRCS_BONUS_ONLY)
else
  OBJDIR = $(OBJ_DIR)
  SRCS   = $(SRCS_MAND)
endif

# =========================
# Objects / Deps
# =========================
OBJS = $(addprefix $(OBJDIR)/,$(SRCS:.c=.o))
DEPS = $(OBJS:.o=.d)

# =========================
# Rules
# =========================
all: $(LIBFT) $(NAME)

run: re
	./$(NAME) 8 7

verbose: CFLAGS += $(DEBUG_FLAGS)
verbose: re

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LDLIBS) -o $(NAME)

$(OBJDIR)/%.o: $(SRC_DIR)/%.c inc/connect4.h
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR) all

# 42 bonus rule
bonus:
	$(MAKE) MODE=bonus all

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf $(OBJ_DIR) $(OBJ_DIR_BONUS)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

-include $(DEPS)

.PHONY: all verbose bonus clean fclean re