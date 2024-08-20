NAME		=	so_long
CC			=	gcc
FLAGS		=	-Wall -Wextra -Werror
MLX			=	mlx/Makefile.gen
INC			=	-I ./inc -I ./mlx -I ./libft
LIB			=	-L ./mlx -lmlx -lXext -lX11 -lm -lbsd
OBJ			=	$(patsubst src%, obj%, $(SRC:.c=.o))
SRC			=	dfs_and_check.c \
				draw.c \
				help.c \
				input_check.c \
				key.c \
				read_and_some_pixel.c \
				resize_img.c \
				so_long.c \
				split.c \
				utils.c

all:		$(MLX) $(LFT) obj $(NAME)

$(NAME):	$(OBJ)
			$(CC) $(FLAGS) -o $@ $^ $(LIB)

$(MLX):
			@echo " [ .. ] | Compiling minilibx.."
			@make -s -C mlx
			@echo " [ OK ] | Minilibx ready!"

$(LFT):
			@echo " [ .. ] | Compiling libft.."
			@make -s -C libft
			@echo " [ OK ] | Libft ready!"

obj:
			@mkdir -p obj

obj/%.o:	src/%.c
			$(CC) $(FLAGS) $(INC) -o $@ -c $<

clean:
			@rm -rf $(OBJ) obj
			@echo "object files removed."

fclean:		clean
			@rm -rf $(NAME)
			@echo "binary file removed."

re:			fclean all

.PHONY:		all clean fclean re
