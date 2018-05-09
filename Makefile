NAME	=	fillit

CC		=	gcc

DIR		=	rendu

SRC		= main.c \
	parsing.c \
	tools.c \
	testing.c

HEADER	= fillit.h

OBJ		= $(SRC:.c=.o)

CFLAGS	=	-Wall -Wextra -Werror
LDFLAGS = -L libft -lft

all		:	$(NAME)

$(NAME)	:	$(OBJ)
			make -C libft
			$(CC) -o $(NAME) $(OBJ) -I $(HEADER) -L libft -lft

%.o		:	%.c fillit.h
			${CC} ${CFLAGS} -I ${HEADER} -c -o $@ $<

clean	:
			@make clean -C libft
			rm -f $(OBJ)

fclean	:	clean
			@make fclean -C libft
			@rm -f $(NAME)

re		:	fclean all

.PHONY	: all, clean, fclean, re
