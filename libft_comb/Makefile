NAME	=	libft.a
INCLUDE	=	./includes
SRC_DIR	=	./srcs
CC		=	gcc
RM		=	rm -f
AR		=	ar rcs
CFLAGS	=	-Wall -Wextra -Werror
SRCS	=	$(shell find $(SRC_DIR) -name '*.c')

.c.o	:
			$(CC) $(CFLAGS) -I $(INCLUDE) -c $< -o $@

OBJS	=	$(SRCS:%.c=%.o)

all	:	$(NAME)

$(NAME)	:	$(OBJS)
			$(AR) $(NAME) $(OBJS)

clean	:
			$(RM) $(OBJS)

fclean	:	clean
			$(RM) $(NAME)

re		:	fclean all

.PHONY	: clean fclean all re
