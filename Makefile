NAME	=	minishell
INCLUDE	=	./include/
SRC_DIR	=	./srcs
OBJ_DIR	=	./obj
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror -g3 -fsanitize=address
RL_INC	=	-I/usr/local/opt/readline/include
RL_LIB	=	-lreadline -L/usr/local/opt/readline/lib
RM		=	rm -f

SRCS	=	$(shell find $(SRC_DIR) -name '*.c' -execdir basename {} \;)
OBJS	:=	$(SRCS:%.c=$(OBJ_DIR)/%.o)

all	:	
		mkdir -p $(OBJ_DIR)
		make $(NAME)

$(NAME)	:	$(OBJS)
		$(CC) $(CFLAGS) $(OBJS) $(RL_LIB) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -I $(INCLUDE) $(RL_INC) -c $< -o $@

clean	:
			$(RM) -r $(OBJ_DIR)

fclean	:	clean
			$(RM) $(NAME)

re		:	fclean all

.PHONY	: clean fclean all re