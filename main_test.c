/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeauman <gbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 11:59:44 by gbeauman          #+#    #+#             */
/*   Updated: 2022/05/18 14:30:24 by gbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

void	treat_pipe_tab(char *cmd_piped, char **envp)
{
	char **tab1;

	tab1 = ft_split(cmd_piped, ' ');
	check_tab1(tab1, envp);
	free (tab1);	
}

void	pipe_tab(char *cmd_line, char **envp)
{
	char **result;
	int	j;

	j = 0;
	result = ft_split_pipe(cmd_line, '|');
	while (result[j])
	{
		treat_pipe_tab(result[j], envp);
		j++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	*cmd;
	
	argc = 0;
	argv = NULL;
	while (1)
	{
        cmd = readline("prompt> ");
        add_history(cmd);
        pipe_tab(cmd, envp);
    }
}