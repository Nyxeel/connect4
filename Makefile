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
	ai.c \
	main.c \
	parse.c \
	init_game.c \
	start_game.c \
	utils.c \
	cleanup.c \
	check_game_state.c \
	grid/game_loop.c \
	grid/input_player.c \
	grid/print_grid.c \
	grid_bonus/render_grid.c \
	grid_bonus/input_line.c \
	grid_bonus/message.c \
	grid_bonus/render_ai_move.c \
	grid_bonus/bonus_game_loop.c \



# =========================
# Bonus replacements/additions
# =========================


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



clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf $(OBJ_DIR) $(OBJ_DIR_BONUS)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

-include $(DEPS)

.PHONY: all verbose clean fclean re
