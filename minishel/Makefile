# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mchalard <mchalard@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/11 13:14:12 by mchalard          #+#    #+#              #
#    Updated: 2022/06/29 16:55:50 by mchalard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc 
export CFLAGS = -Wextra -Werror -Wall
LDFLAGS = -lreadline -L$(HOME)/.brew/Cellar/readline/8.1.2/lib

SRCS_DIR = ./src
OBJS_DIR = ./objs
SRCS =	main.c\
		parsing/parsing.c\
		parsing/error_red.c\
		parsing/parse_red.c\
		parsing/check_valid_cmd.c\
		exec/exec_tab.c\
		exec/built_in.c\
		exec/pipe.c\
		exec/exec_red.c\
		exec/ft_exec_single.c\
		built_in/cd.c\
		built_in/echo.c\
		built_in/env.c\
		built_in/exit.c\
		built_in/export.c\
		built_in/pwd.c\
		built_in/unset.c\
		quotes_dollars/manage_dollar.c\
		quotes_dollars/new_parse_quotes.c\
		quotes_dollars/replace_tab.c\
		quotes_dollars/calcul_mem.c\
		redirection/check_heredocs.c\
		redirection/stdin_out.c\
		utils/utils_part_one.c\
		utils/utils_part_two.c\
		utils/free_close.c\
		utils/init.c\
		utils/utils_red.c\
		utils/utils_cd.c\
		utils/utils_cd_2.c\
		utils/utils_export.c\
		utils/utils_quotes.c\
		utils/ft_itoa.c\
		utils/ft_atoi.c\
		utils/ft_split.c\
		signals/signal.c

OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))

vpath %.c $(SRCS_DIR)

RM = rm -f

.PHONY: all re clean fclean debug

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAG) -o $(NAME) $(OBJS) $(LDFLAGS)

$(OBJS_DIR):
	mkdir -p $(dir $(OBJS))

$(OBJS_DIR)/%.o : %.c | $(OBJS_DIR)
	$(CC) $(CFLAGS)  -o $@ -c $^

debug: CFLAGS += -g3 -fsanitize=address -fno-omit-frame-pointer
debug: $(OBJS) $(NAME)

clean :
	$(RM) -r $(OBJS_DIR)

fclean : clean
	$(RM) $(NAME)

re : fclean all