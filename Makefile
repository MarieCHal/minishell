# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbeauman <gbeauman@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/11 13:14:12 by mchalard          #+#    #+#              #
#    Updated: 2022/06/15 14:29:29 by gbeauman         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc -I $HOME/.brew/Cellar/readline/8.1.2/include
SRC =	main_test.c\
		split_parse/ft_split.c\
		split_parse/parsing.c\
		exec/exec.c\
		exec/treat_tab1.c\
		built_in/cd.c\
		built_in/echo.c\
		built_in/env.c\
		built_in/exit.c\
		built_in/export.c\
		built_in/pwd.c\
		built_in/unset.c\
		utils.c\
		envp_init.c\

FLAGS = -Wall -Werror -Wextra -g3 -fsanitize=address -fno-omit-frame-pointer
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