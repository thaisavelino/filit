NAME	=	fillit

CC		=	gcc

SDIR		=	./srcs

IDIR		=	./srcs

ODIR		=	./srcs

LDIR		=	./libft

SRC		= main.c \
	parsing.c \
	tools.c \
	display.c

HEADERS	=	$(IDIR)/fillit.h

OBJ		=	$(SRC:.c=.o)

_OBJ	=	$(patsubst %, $(ODIR)/%, $(OBJ))

CFLAGS	=	-Wall -Wextra -Werror

LDFLAGS	=	-L libft -lft

all		:	$(NAME)

$(NAME)	:	$(_OBJ)
			@echo "Compiling..."
			@$(MAKE) -C libft
			@$(CC) -o $(NAME) $(_OBJ) -L libft -lft
			@echo "[96mFillit [92mCompiled[0m"

%.o		:	%.c $(HEADERS)
			@$(CC) $(CFLAGS) -I $(HEADERS) -c -o $@ $<

clean	:
			@$(MAKE) clean -C libft
			@echo "Cleaning the [96mFillit [0mfiles..."
			@rm -f $(_OBJ)
			@echo "[92mDone[0m"

fclean	:	clean
			@rm -f $(LDIR)/libft.a
			@rm -f $(NAME)

re		:	fclean all

.PHONY	: all, clean, fclean, re
