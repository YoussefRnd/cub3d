CC = cc
CFLAGS = -Wall -Werror -Wextra
SRC_DIR = src
OBJ_DIR = obj
NAME = cub3d
LIBFT_DIR = libft

SRCS = $(wildcard $(SRC_DIR)/*.c get_next_line/*.c) main.c
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L$(LIBFT_DIR) -lft

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS): | $(OBJ_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	make -C $(LIBFT_DIR) clean
	rm -rf $(OBJ_DIR) $(NAME)

fclean: clean
	make -C $(LIBFT_DIR) fclean
	rm -f $(NAME)