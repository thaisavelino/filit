NAME	=	fillit

CC		=	gcc

SDIR		=	./srcs

IDIR		=	./srcs

ODIR		=	./srcs

SRC		= main.c \
	parsing.c \
	tools.c

HEADER	= fillit.h

_OBJ	=	$(SRC:.c=.o)

OBJ		=	$(patsubst %, $(ODIR)/%, $(_OBJ))

CFLAGS	=	-Wall -Wextra -Werror

LDFLAGS = -L libft -lft

all		:	$(NAME)

$(NAME)	:	$(OBJ)
			@$(MAKE) -C libft
			$(CC) -o $(NAME) $(OBJ) -L libft -lft

%.o		:	%.c fillit.h
			${CC} ${CFLAGS} -I ${HEADER} -c -o $@ $<

clean	:
			@$(MAKE) clean -C libft
			rm -f $(OBJ)

fclean	:	clean
			@$(MAKE) fclean -C libft
			@rm -f $(NAME)

re		:	fclean all

.PHONY	: all, clean, fclean, re
