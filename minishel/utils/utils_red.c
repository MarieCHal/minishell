/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_red.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchalard <mchalard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 09:29:22 by mchalard          #+#    #+#             */
/*   Updated: 2022/06/27 13:39:59 by mchalard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_print_error_red(char *token)
{
	printf("syntax error near unexpected token `%s'\n", token);
	exit_status = 258;
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

int	ft_search_red(char **cmd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmd[j])
	{
		i = 0;
		while (cmd[j][i])
		{
			if (cmd[j][i] == '<' || cmd[j][i] == '>')
				 return (1);
			i++;
		}
		j++;
	}
	return (0);
}

//to copy the lines when parsing redirections
char	*ft_strncpy_red(char *str, int start, int end)
{
	int		i;
	int		j;
	char	*dest;

	dest = malloc(sizeof(char) * (ft_len_red(str, start) + 1));
	j = 0;
	i = start;
	while (i < end)
	{
		dest[j] = str[i];
		j++;
		i++;
	}
	dest[j] = '\0';
	return (dest);
}

int	ft_len_post_red(char **tab)
{
	int	j;
	int	len;

	j = 0;
	len = 0;
	while (tab[j])
	{
		if (tab[j][0] != '<' && tab[j][0] != '>')
			len++; 
		j++;
	}
	return (len - 1);
}

void	close_fd(t_fd *files)
{
	if (files->heredocs == 1 && files->tab_in != NULL)
		free_tab(files->tab_in);
	if (files->fd_in != -1)
		close(files->fd_in);
	if (files->fd_out != -1)
		close(files->fd_out); 
}

//initialize the struct for redirections
//-------->replace the initialization of fd in and out at -1
void	ft_init_red(t_fd *files)
{
	files->append = 0;
	files->fd_in = -1;
	files->fd_out = -1;
	files->heredocs = 0;
	files->red = 0;
	files->error = 0;
	files->tab_in = NULL;
}
