NAME	=	fillit

CC		=	gcc

DIR		=	rendu

SRC		= main.c \
	parsing.c \
	tools.c

OBJ		=	$(SRC:.c=.o)

CFLAGS	=	-Wall -Wextra -Werror -I ./libft

all		:	$(NAME)

$(NAME)	:	$(OBJ)
			@make -C libft
			$(CC) -o $(NAME) $(OBJ) -L libft -lft

clean	:
			@make clean -C libft
			rm -f $(OBJ)

fclean	:	clean
			@rm -f $(NAME)

re		:	fclean all

.PHONY	: all, clean, fclean, re
