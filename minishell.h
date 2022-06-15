/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeauman <gbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 13:48:44 by mchalard          #+#    #+#             */
/*   Updated: 2022/06/15 13:50:35 by gbeauman         ###   ########.fr       */
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

typedef struct s_tab
{
	char	*old_pwd;
	char	*dir;
	char	*pwd_var;
	char	*oldpwd_var;
	char	**envp;
	char	*just_path;
	char	*home_path;
	char	*another_oldpwd;
}			t_tab;


int     main(int argc, char **argv, char **envp);
char    **ft_split(char const *s, char c);
char	**ft_split_pipe(char const *s, char c);
int     ft_quotes(const char *str, int i, char q);
int     ft_count_quotes(const char *str, int i, char q);
size_t	ft_strlen(const char *s);
char	*ft_strjoin(char *s1, char *s2);
void    check_exec(char *command);
int     check_tab1(char **tab1, t_tab *tab);
int     built_in(char *command);
char    *get_pwd();
char	*ft_just_pwd();
void	*ft_pwd(t_tab *tab);
void    ft_echo(char *str);
void    ft_exit();
void    ft_cd(char *path, t_tab *tab);
char    *get_variable_value(char *variable);
void	ft_get_env(t_tab *tab);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	envp_init(t_tab *tab, char **envp);
char	*ft_strdup(const char *s1);
void	ft_export(t_tab *tab, char **var);

#endif