/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeauman <gbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 11:59:44 by gbeauman          #+#    #+#             */
/*   Updated: 2022/06/14 10:37:52 by gbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

void	treat_pipe_tab(char *cmd_piped, t_tab *tab)
{
	char **tab1;

	tab1 = ft_split(cmd_piped, ' ');
	check_tab1(tab1, tab);
	free (tab1);	
}

void	pipe_tab(char *cmd_line, t_tab *tab)
{
	char **result;
	int	j;

	j = 0;
	result = ft_split_pipe(cmd_line, '|');
	while (result[j])
	{
		treat_pipe_tab(result[j], tab);
		j++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	*cmd;
	t_tab 	tab = {.old_pwd = NULL};
	
	//tab.envp = envp;
	envp_init(&tab, envp);
	tab.dir = NULL;
	tab.pwd_var = "PWD=";
	tab.oldpwd_var = "OLDPWD=";
	tab.home_path = "/Users/gbeauman";
	argc = 0;
	argv = NULL;
	while (1)
	{
        cmd = readline("prompt> ");
        add_history(cmd);
        pipe_tab(cmd, &tab);
    }
}