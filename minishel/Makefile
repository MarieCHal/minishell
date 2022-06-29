# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbeauman <gbeauman@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/11 13:14:12 by mchalard          #+#    #+#              #
#    Updated: 2022/06/29 16:34:03 by gbeauman         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc -I $HOME/.brew/Cellar/readline/8.1.2/include
SRC =	main_test.c\
		split_parse/ft_split.c\
		split_parse/parsing.c\
		exec/exec_tab.c\
		exec/built_in.c\
		exec/pipe.c\
		exec/exec_red.c\
		exec/ft_exec_single.c\
		built_in/cd.c\
		built_in/utils_cd.c\
		built_in/utils_cd_2.c\
		built_in/echo.c\
		built_in/env.c\
		built_in/exit.c\
		built_in/export.c\
		built_in/utils_export.c\
		built_in/pwd.c\
		built_in/unset.c\
		quotes_dollards/manage_dollard.c\
		quotes_dollards/new_parse_quotes.c\
		quotes_dollards/replace_tab.c\
		quotes_dollards/calcul_mem.c\
		redirection/check_heredocs.c\
		redirection/parse_red.c\
		redirection/stdin_out.c\
		utils/cat.c\
		utils/utils.c\
		utils/malloc_free_close.c\
		utils/utils_red.c\
		utils/ft_itoa.c\
		utils/envp_init.c\
		check_valid_cmd.c\

FLAGS = -Wall -Werror -Wextra #-g3 -fsanitize=address -fno-omit-frame-pointer
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