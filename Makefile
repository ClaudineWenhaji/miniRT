NAME            = miniRT
CC              = cc
CFLAGS          = -Wall -Wextra -Werror -Iincludes -Ilibft
LDFLAGS         = -Llibft -lft
MLX_FLAGS		= -L$(MLX_DIR) -lmlx -L/usr/lib -lXext -lX11 -lm -lbsd

SRCS            = $(shell find ./srcs -name "*.c")
OBJS            = $(SRCS:%.c=%.o)
INC_DIR         = includes
LIBFT_DIR       = libft
MLX_DIR			= minilibx-linux
LIBFT           = $(LIBFT_DIR)/libft.a
MLX				= $(MLX_DIR)/libmlx.a

GREEN           = \033[0;32m
RED             = \033[0;31m
YELLOW          = \033[0;33m
RESET           = \033[0m

all: $(MLX) $(LIBFT) $(NAME)

$(LIBFT):
	@printf "$(YELLOW)Compiling libft...$(RESET)\n"
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory

$(NAME): $(OBJS) $(LIBFT)
	@printf "$(YELLOW)Linking $(NAME)...$(RESET)\n"
	@$(CC) $(OBJS) $(LDFLAGS) $(MLX_FLAGS) -o $(NAME)
	@printf "$(GREEN)$(NAME) created successfully!$(RESET)\n"

%.o: %.c
	@printf "$(YELLOW)Compiling $<...$(RESET)\n"
	@$(CC) $(CFLAGS) -I$(MLX_DIR) -c $< -o $@

$(MLX):
	@if [ ! -f $(MLX) ]; then \
		printf "$(YELLOW)Compiling MinilibX $<...$(RESET)\n"; \
		chmod +x $(MLX_DIR)/configure; \
		make -C $(MLX_DIR) --no-print-directory > /dev/null 2>&1 || true; \
		printf "$(GREEN)MinilibX compiled!$(RESET)\n"; \
	fi

clean:
	@make clean -C $(LIBFT_DIR) --no-print-directory
	@make clean -C $(MLX_DIR) --no-print-directory
	@printf "$(RED)Deleting object files...$(RESET)\n"
	@rm -f $(OBJS)

fclean: clean
	@printf "$(RED)Deleting $(NAME)...$(RESET)\n"
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

gdb: CFLAGS += -g3
gdb: re

test: re
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes -s ./miniRT

.PHONY: all clean fclean re
