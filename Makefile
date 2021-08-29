NAME = minishell

HEADER = minishell.h

CC = gcc

CFLAGS = -g -Wall -Wextra -Werror -I/usr/local/opt/readline/include

SRC = 	parser.c\
		utils.c\
		ft_exec.c\
		ft_exec_pwd.c\
		ft_exec_echo.c\
		ft_exec_exit.c\
		main.c\

LIBFT = libft.a

READLINE_LIB =	-lreadline \
				-L/usr/local/opt/readline/lib \

OBJ = $(SRC:.c=.o)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

all: $(NAME)

$(LIBFT):
	@$(MAKE) -C libft
	@$(MAKE) fclean
	@mv libft/$(LIBFT) .

$(NAME): $(LIBFT) $(OBJ) $(HEADER)
	$(CC) -o $(NAME) ${LIBFT} $(OBJ) $(READLINE_LIB)

re: fclean all

clean:
	rm -f *.o $(OBJ)
	@$(MAKE) -C libft clean

fclean: clean
	rm -f $(NAME) $(LIBFT)
