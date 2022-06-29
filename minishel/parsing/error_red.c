/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_red.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchalard <mchalard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 16:48:54 by mchalard          #+#    #+#             */
/*   Updated: 2022/06/28 16:47:59 by mchalard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_print_error_red(char *token)
{
	printf("syntax error near unexpected token `%s'\n", token);
	g_exit_status = 258;
	return (0);
}

//checks the number of red before executing the cmd
//--------------    leaks!!!!!!!!
int	ft_check_parse_error(char **cmd)
{
	int		i;
	char	**cmd_parsed;
	char	**cmd_red;

	i = 0;
	while (cmd[i])
	{
		cmd_parsed = ft_split(cmd[i], ' ');
		if (!ft_search_red(cmd_parsed))
			i++;
		else
		{
			cmd_red = ft_parse_red(cmd_parsed);
			if (!error_red(cmd_red))
			{
				free_tab(cmd_parsed);
				free_tab(cmd_red);
				return (0);
			}
			free_tab(cmd_red); 
			i++;
		}
		free_tab(cmd_parsed); 
	}
	return (1);
}

//check error in number of red
//takes as argument the cmd parsed with the red at the right place
int	error_red(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if ((cmd[i][0] == '>' || cmd[i][0] == '<') && cmd[i + 1] != 0)
		{
			i++;
			if (cmd[i][0] == '<' || cmd[i][0] == '>')
				return (ft_print_error_red(cmd[i]));
		}
		else if (cmd[i][0] == '>' || cmd[i][0] == '<')
			return (ft_print_error_red(cmd[i]));
		i++;
	}
	return (1);
}