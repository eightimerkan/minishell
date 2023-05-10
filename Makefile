NAME = minishell

CC = gcc

RM = rm -rf

INCLUDE=-I

CFLAGS = -Wall -Wextra -Werror

SRCS = $(wildcard src/*.c) main.c

OBJ = $(SRCS:.c=.o)

OBJ_LIB = $(wildcard lib/libft/*.o)

all: ./lib/libft/libft.a $(NAME)

./lib/libft/libft.a:
		make -C lib/libft

$(NAME): $(OBJ)
		$(CC) -lreadline $(CFLAGS) $(OBJ) ${OBJ_LIB} -o $(NAME)

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
		$(RM) $(OBJ) $(OBJ_LIB)

fclean: clean
		$(RM) $(NAME) ${CHECKER_NAME} *.o
		rm -f lib/libft/libft.a

re: fclean all

.PHONY: all clean fclean re
