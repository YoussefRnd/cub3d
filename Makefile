NAME = cub3D

CC = cc
CFLAGS = -Wall -Werror -Wextra -O3
MLX_FLAGS = -framework Cocoa -framework OpenGL -framework IOKit -lglfw -L"/Users/$(USER)/goinfre/homebrew/Cellar/glfw/3.4/lib"
RM = rm -fr
MKDIR = mkdir -p

LIBFT = lib/Libft
LIBFT_ARCH = -L$(LIBFT) -lft

MLX =  lib/MLX42
MLX_ARCH = $(MLX)/build/libmlx42.a

OBJ_DIR = obj
INC_DIR = inc

SRCS = main.c $(wildcard raycaster/*.c) $(wildcard parser/*.c) $(wildcard get_next_line/*.c) $(wildcard textures/*.c)

OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(LIBFT)/libft.a:
	@$(MAKE) -C $(LIBFT)

$(OBJ_DIR)/%.o: %.c $(INC_DIR)/cub3d.h
	@$(MKDIR) $(@D)
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -I $(INC_DIR) -I $(LIBFT) -I $(MLX)/include -c $< -o $@

$(NAME): $(OBJS) $(LIBFT)/libft.a
	@echo "Building $@..."
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT_ARCH) $(MLX_ARCH) $(MLX_FLAGS)
	@echo "$@ is ready!"

clean:
	@echo "Cleaning object files..."
	@$(RM) $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT) clean

fclean: clean
	@echo "Cleaning $(NAME)..."
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT) fclean

re: fclean all

.PHONY: all clean fclean re