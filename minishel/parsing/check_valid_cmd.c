/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchalard <mchalard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 12:21:02 by mchalard          #+#    #+#             */
/*   Updated: 2022/06/29 16:17:11 by mchalard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_cmd_to_exec(char *tab)
{
	char	**parse_space;
	char	**parse_red;
	char	**new;

	parse_space = ft_split(tab, ' ');
	if ((ft_search_red(parse_space)) == 0)
		return (parse_space);
	parse_red = ft_parse_red(parse_space);
	new = post_red(parse_red);
	free_tab(parse_space);
	return (new);
}

int	ft_check_access(char **cmd_tab, char **my_paths)
{
	int		i;
	char	*cmd_path;
	char	*cmd;
	int		error;

	i = 0;
	while (my_paths[i])
	{
		cmd_path = ft_strjoin(my_paths[i], "/");
		cmd = ft_strjoin(cmd_path, cmd_tab[0]);
		free(cmd_path);
		error = access(cmd, X_OK);
		if (error != -1)
		{
			free (cmd);
			return (2);
		}
		free (cmd);
		i++;
	}
	return (error);
}

int	ft_builin_absolute(char **cmd_tab, char *cmd_pipe)
{
	if (built_in(cmd_tab[0]) != 0)
	{
		free_tab(cmd_tab);
		return (0);
	}
	else if (access(cmd_pipe, X_OK) == 0)
	{
		free_tab(cmd_tab);
		return (0);
	}
	return (1);
}

void	ft_no_cmd(char **cmd_tab, char **my_paths)
{
	int	error;
	
	error = ft_check_access(cmd_tab, my_paths);
	if (error == -1 && cmd_tab[0] != NULL)
			printf("bash: %s: command not found\n", cmd_tab[0]);
	free_tab(cmd_tab);
}

void	ft_unvalid_cmd(char **cmd_pipe, t_tab *tab)
{
	int		j;
	char	**cmd_tab;
	char	**cmd_parsed;
	char	*path_envp;
	char	**my_paths;

	j = 0;
	path_envp = copy_new_line(getenv("PATH"));
	my_paths = ft_split(path_envp, ':');
	while (cmd_pipe[j])
	{
		cmd_parsed = ft_cmd_to_exec(cmd_pipe[j]);
		cmd_tab = replace_quotes(cmd_parsed, tab);
		free_tab(cmd_parsed);
		if (!ft_builin_absolute(cmd_tab, cmd_pipe[j]))
			j++;
		else
		{
			ft_no_cmd(cmd_tab, my_paths);
			j++;
		}
	}
	free(path_envp);
	free_tab(my_paths);
}
