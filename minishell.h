/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchalard <mchalard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 13:48:44 by mchalard          #+#    #+#             */
/*   Updated: 2022/05/19 11:45:25 by mchalard         ###   ########.fr       */
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
int	    ft_strncmp(const char *s1, const char *s2, size_t n);
void	free_tab(char **tab_to_free);
void    check_exec(char *command);
int    check_cmd(char **tab);
int     built_in(char *command);
char    *get_pwd();
void	ft_pwd();
void    ft_echo(char **tab);
void    ft_exit();
void    ft_cd(char *path);
char    *get_variable_value(char *variable);
char    *check_quotes(char *line);
char    **parsed_tab(char **tab);

#endif