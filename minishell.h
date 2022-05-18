/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchalard <mchalard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 13:48:44 by mchalard          #+#    #+#             */
/*   Updated: 2022/05/18 12:19:55 by mchalard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "readline/readline.h"
# include "readline/history.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
#include <dirent.h>
#include <sys/types.h>

int     main(void);
char    **ft_split(char const *s, char c);
char	**ft_split_pipe(char const *s, char c);
int     ft_quotes(const char *str, int i, char q);
int     ft_count_quotes(const char *str, int i, char q);
size_t	ft_strlen(const char *s);
char	*ft_strjoin(char *s1, char *s2);
void    check_exec(char *command);
int     check_tab1(char **tab1);
int     built_in(char *command);
char    *get_pwd();
void	ft_pwd();
void    ft_echo(char *str);
void    ft_exit();
void    ft_cd(char *path);
char    *get_variable_value(char *variable);

#endif