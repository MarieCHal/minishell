/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchalard <mchalard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 11:59:44 by gbeauman          #+#    #+#             */
/*   Updated: 2022/05/17 16:36:34 by mchalard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

void	treat_pipe_tab(char *cmd_piped)
{
	char **tab1;

	tab1 = ft_split(cmd_piped, ' ');
	check_tab1(tab1);
	free (tab1);	
}

void	pipe_tab(char *cmd_line)
{
	char **result;
	int	j;

	j = 0;
	result = ft_split_pipe(cmd_line, '|');
	while (result[j])
	{
		treat_pipe_tab(result[j]);
		j++;
	}
}

int	main(void)
{
	char	*cmd;
	
	while (1)
	{
        cmd = readline("prompt> ");
        add_history(cmd);
        pipe_tab(cmd);
    }
}