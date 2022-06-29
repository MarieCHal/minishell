/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchalard <mchalard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 11:59:44 by gbeauman          #+#    #+#             */
/*   Updated: 2022/06/29 16:18:20 by mchalard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

int	g_exit_status = 0;

void	pipe_tab(char *cmd_line, t_tab *tab)
{
	char **result;
	
	result = NULL;
	if (!check_error_nb_quotes(cmd_line))
		return;
	result = ft_split(cmd_line, '|');
	if (ft_count_pipes(cmd_line, result) == 1)
		return;
	if (!ft_check_parse_error(result))
	{
		free_tab(result);
		return;
	}
	ft_unvalid_cmd(result, tab);
	if (ft_count_cmd(result, tab) == 1)
	{
		free(cmd_line);
		return;
	}
	check_cmd(result, tab);
	free_tab(result);
	free(cmd_line);
}



int	main(int argc, char **argv, char **envp)
{
	char	*cmd;
	t_tab 	tab = {.old_pwd = NULL};
	struct	termios sig;
	
	init_signals(&sig);
	ft_init_built_in(&tab);
	envp_init(&tab, envp);
	argv = NULL;
	if (argc == 1)
	{
		while (1)
		{
        	cmd = readline("prompt> ");
			if (!cmd)
				break;
			add_history(cmd);
        	pipe_tab(cmd, &tab);
    	}
		tcsetattr(STDIN_FILENO, TCSANOW, &sig);
	}
	return (g_exit_status);
}