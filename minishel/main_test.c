/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchalard <mchalard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 11:59:44 by gbeauman          #+#    #+#             */
/*   Updated: 2022/06/09 14:39:54 by mchalard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

//pid_t child_pid = - 1;

//check cat
int	check_cat(char **result)
{
	int	i;
	int	nb_cat;
	const char *cat;
	char **cmd;
	char *rd;
	
	i = 0;
	nb_cat = 0;
	cat = "cat\0";
	if (result[0] == NULL)
		return(0);
	cmd = ft_split(result[0], ' ');
	if (ft_strncmp(cmd[0], cat, 4) == 0)
	{
		i++;
		nb_cat++;
		free_tab(cmd);
		if (result[i] == NULL)
			return(nb_cat);
		cmd = ft_split(result[i], ' ');
		while ((ft_strncmp(cmd[0], cat, 4) == 0))
		{
			free_tab(cmd);
			i++;
			nb_cat++;
			if (result[i] == NULL)
				return(nb_cat);
			cmd = ft_split(result[i], ' ');
		}
	}
	free_tab(cmd);
	while (nb_cat != 0)
	{
		rd = readline("");
		nb_cat--;
		free(rd);
	}
	return (0);
}

void	pipe_tab(char *cmd_line)
{
	char **result;
	int		j;
	
	j = 0;
	result = ft_split(cmd_line, '|');
	while (result[j])
	{
		printf("%s\n", result[j]);
		j++;
	}
	check_cmd(result);
	check_cat(result);
	free_tab(result);
}

int	main(void)
{
	char	*cmd;
	
	//signal(SIGINT, sig_int);
	while (1)
	{
        cmd = readline("prompt> ");
		add_history(cmd);
        pipe_tab(cmd);
		free(cmd);
    }
	return (0);
}