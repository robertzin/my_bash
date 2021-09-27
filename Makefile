# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yjama <yjama@student.21-school.ru>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/16 20:45:39 by oharmund          #+#    #+#              #
#    Updated: 2021/09/26 19:21:50 by yjama            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

HEADERS		= ./headers

SRCS		=	ft_main.c\
				pipe.c\
				pipe_utils.c\
				redirect.c\
				redirect_utils.c\
				inc_shlvl.c\
				ft_errors.c\
				ft_signal.c\
				./parser/ft_cmd_parse.c\
				./parser/ft_parser_utils.c\
				./parser/ft_quotes_symbol.c\
				./parser/ft_dollar.c\
				./parser/ft_rd_filename_delimiter.c\
				./parser/ft_redir_parse.c\
				./parser/ft_redir_utils.c\
				./parser/parser_env.c\
				./parser/parser.c\
				./exec/utils.c\
				./exec/utils_norm.c\
				./exec/ft_exec.c\
				./exec/ft_exec_cd.c\
				./exec/ft_exec_echo.c\
				./exec/ft_exec_exit.c\
				./exec/ft_exec_export.c\
				./exec/ft_exec_pwd.c\
				./exec/ft_exec_unset.c\
				./exec/executing_commands.c\
				./exec/executing_commands_utils.c\

LIB_PATH	= ./libft

LIB			= libft.a

OBJS		= $(SRCS:.c=.o)

DEP			= $(OBJS:.o=.d)

NAME		= minishell

GCC			= gcc

RM			= rm -f

GFLAGS		= -Wall -Wextra -Werror -I $(HEADERS)

RL_FLAGS	= -lreadline -L/Users/$(USER)/.brew/Cellar/readline/8.1/lib/ -I/Users/$(USER)/.brew/Cellar/readline/8.1/include

.c.o:
			$(GCC) $(GFLAGS) -c -MMD $< -o $(<:.c=.o)

$(NAME):	$(OBJS)
			$(MAKE) -C $(LIB_PATH)
			cp $(LIB_PATH)/$(LIB) ./
			$(GCC) $(GFLAGS) -o $(NAME) -L. -lft $(RL_FLAGS) $(OBJS)

all:		$(NAME)

clean:
			$(MAKE) clean -C $(LIB_PATH)
			$(RM) $(OBJS)

fclean:		clean
			$(MAKE) fclean -C $(LIB_PATH)
			$(RM) $(NAME) $(LIB)
			$(RM) $(DEP)

re:			fclean all

.PHONY:		all clean fclean re

-include $(DEP)

