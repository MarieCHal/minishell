/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchalard <mchalard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 11:59:44 by gbeauman          #+#    #+#             */
/*   Updated: 2022/05/19 11:54:02 by mchalard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

void	treat_pipe_tab(char *cmd_piped)
{
	char **tab;
	
	tab = parsed_tab(ft_split(cmd_piped, ' '));
	check_cmd(tab);
	free_tab(tab);	
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
	free_tab(result);
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