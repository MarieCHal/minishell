# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mchalard <mchalard@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/11 13:14:12 by mchalard          #+#    #+#              #
#    Updated: 2022/06/16 16:06:36 by mchalard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc -I $HOME/.brew/Cellar/readline/8.1.2/include
SRC =	tmp.c\
		split_parse/ft_split.c\
		split_parse/parsing.c\
		exec/exec_tab.c\
		exec/built_in.c\
		exec/new_pipe.c\
		built_in/cd.c\
		built_in/echo.c\
		built_in/env.c\
		built_in/exit.c\
		built_in/export.c\
		built_in/pwd.c\
		built_in/unset.c\
		utils.c\
		quotes_dollards/manage_dollard.c\
		quotes_dollards/new_parse_quotes.c\
		quotes_dollards/replace_tab.c\
		quotes_dollards/calcul_mem.c\
		signals/signal.c\
		redirection/check_in.c\
		redirection/check_out.c\
		redirection/parse_red.c\
		redirection/stdin_out.c\
		redirection/utils_red.c\
		new_split.c\
		

FLAGS = -Wall -Werror -Wextra -g3 #-fsanitize=address -fno-omit-frame-pointer
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(SRC) -lreadline -framework OpenGL -framework AppKit -o $(NAME)

clean:
	rm -f $(OBJ)
fclean: clean
	rm -f $(NAME)
re: fclean all

.PHONY: all clean fclean re