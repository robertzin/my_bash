NAME = minishell

HEADER = minishell.h

USER = robert_zin#поменять на свой юзернейм

CC = gcc

CFLAGS = -g -Wall -Wextra -Werror

SRC = 	libft.c\
		main.c

READLINE_LIB =	-lreadline \
				-L /Users/$(USER)/.brew/opt/readline/lib \
				-I /Users/$(USER)/.brew/opt/readline/include

OBJ = $(SRC:.c=.o)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	$(CC) -o $(NAME) $(OBJ) $(READLINE_LIB)

re: fclean all

clean:
	rm -f *.o $(OBJ)

fclean: clean
	rm -f $(NAME)
