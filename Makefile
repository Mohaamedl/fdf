NAME = fdf
NAME_BONUS = fdf_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror -Iinclude -Imlx -Ilibft/inc
LDFLAGS = -L. -lmlx_Linux -lXext -lX11 -lm -lz

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

SRC_DIR = src
SRC_BONUS_DIR = src_bonus
OBJ_DIR = obj
OBJ_BONUS_DIR = obj_bonus

# Mandatory sources
SRC = main.c hooks.c

# Bonus sources (minimal, using shared code from src when possible)
SRC_BONUS = main_bonus.c main_bonus_utils.c render_bonus.c hooks_keys_bonus.c hooks_mouse_bonus.c overlay_bonus.c demo_mode_bonus.c utils_bonus.c hooks_utils_bonus.c hooks_keys_utils_bonus.c hooks_mouse_utils_bonus.c render_utils_bonus.c render_setup_bonus.c

# Shared sources that both mandatory and bonus need
SHARED_SRC = parse.c render.c render_utils.c mlx_init.c view.c projection.c color.c utils.c parse_utils.c

OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o) $(SHARED_SRC:%.c=$(OBJ_DIR)/%.o)
OBJ_BONUS = $(SRC_BONUS:%.c=$(OBJ_BONUS_DIR)/%.o) \
			$(SHARED_SRC:%.c=$(OBJ_BONUS_DIR)/%.o)

.PHONY: all clean fclean re bonus

all: $(NAME)

bonus: $(NAME_BONUS)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) $(LDFLAGS)

$(NAME_BONUS): $(LIBFT) $(OBJ_BONUS)
	$(CC) $(CFLAGS) -o $(NAME_BONUS) $(OBJ_BONUS) $(LIBFT) $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_BONUS_DIR)/%.o: $(SRC_BONUS_DIR)/%.c | $(OBJ_BONUS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_BONUS_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_BONUS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_BONUS_DIR):
	mkdir -p $(OBJ_BONUS_DIR)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -rf $(OBJ_DIR) $(OBJ_BONUS_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all
