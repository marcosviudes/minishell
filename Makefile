NAME		= minishell

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -g3#-Wpedantic -O3
DFLAGS		= -g 
INCLUDES	= -I ./includes -I./libft

RM			= rm -rf
MKDIR		= mkdir -p

LIBFT_DIR	= ./libft
LIBFT_A		= $(LIBFT_DIR)/libft.a
SRC_DIR		= src/
LIST_DIR	= dllist/
TEST_DIR	= $(SRC_DIR)test/

SRC			= main.c\
			prompt.c\
			$(LIST_DIR)dllst_clear.c\
			$(LIST_DIR)dllst_first.c\
			$(LIST_DIR)dllst_last.c\
			$(LIST_DIR)dllst_new.c\
			$(LIST_DIR)dllst_next.c\
			$(LIST_DIR)dllst_prev.c\
			$(LIST_DIR)dllstadd_back.c\
			$(LIST_DIR)dllstadd_front.c

TEST		= $(TEST_DIR)test1.c\
			$(TEST_DIR)test2.c
SRC_F	= $(addprefix $(SRC_DIR), $(SRC))
OBJS	= $(SRC_F:%.c=%.o)

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $^

$(NAME): $(OBJS) ./includes/minishell.h
	make -C $(LIBFT_DIR)
	$(CC) $(OBJS) $(CFLAGS) $(INCLUDES) $(LIBFT_A) -o $(NAME)


.PHONY:	all clean fclean re

normi: fclean
	norminette src/*
	norminette includes/*
	norminette libft/*.c libft/*.h

clean:
	@make -C $(LIBFT_DIR) clean
	$(RM) $(NAME) $(OBJS)
	$(RM) test*

fclean: clean
	@make -C $(LIBFT_DIR) fclean
re: fclean all


test1:
	gcc ./src/tests/test1.c -Iincludes -o test1

test2:
	gcc ./src/tests/test2.c -Iincludes -o test2
debug:
	make re CFLAGS=-g3

