##
## EPITECH PROJECT, 2019
## PSU_2018_malloc
## File description:
## Makefile
##

CC=			gcc

SRC=		malloc.c	\
			show_alloc_mem.c

OBJ=		$(SRC:.c=.o)

NAME=		libmy_malloc.so

CFLAGS=		-Wall -Wextra -Werror

CPPFLAGS=	-I.

RM=			rm -f

all:		$(NAME)

$(NAME):	$(OBJ)
			$(CC) $(CFLAGS) $(SRC) -shared -fPIC -o $(NAME)

clean:
			$(RM) $(OBJ)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
