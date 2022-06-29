/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeauman <gbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 11:59:44 by gbeauman          #+#    #+#             */
/*   Updated: 2022/06/28 14:52:51 by gbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

int	exit_status = 0;

void	pipe_tab(char *cmd_line, t_tab *tab)
{
	char **result;
	
	result = NULL;
	if (!cmd_line)
		return;
	if (!check_error_nb_quotes(cmd_line))
		return;
	result = ft_split(cmd_line, '|');
	if (!ft_check_parse_error(result))
	{
		free_tab(result);
		return;
	}
	ft_unvalid_cmd(result);
	if (ft_count_cmd(result, tab) == 1)
	{
		free(cmd_line);
		return;
	}
	check_cmd(result, tab);
	check_cat(result);
	free_tab(result);
	free(cmd_line);
}



int	main(int argc, char **argv, char **envp)
{
	char	*cmd;
	t_tab 	tab = {.old_pwd = NULL};
	//struct	termios sig;
	
	//init_signals(&sig);
	//signal(SIGINT, sig_int);
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
		//free(cmd);
    }
	//tcsetattr(STDIN_FILENO, TCSANOW, &sig);
	return (0);
}