/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchalard <mchalard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 16:41:47 by mchalard          #+#    #+#             */
/*   Updated: 2022/06/29 15:06:42 by mchalard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *get_path(t_tab *tab)
{
	int	i;
	int	len;
	int	p;
	char *path;

	i = 0;
	p = 0;
	len = 0;
	while (tab->envp[i])
	{
		if (ft_strncmp(tab->envp[i], "PATH=\0", 5) == 0)
		{
			while (tab->envp[i][len])
				len++;
			path = malloc(sizeof(char) * (len - 5 + 1));
			len = 4;
			while (tab->envp[i][len])
				path[p++] = tab->envp[i][len++];
			path[p] = '\0';
			return(path);
		}
		i++;
	}
	return(NULL);
}

int	ft_execve(char **input, t_tab *tab)
{
	int		i;
	char	*path_envp;
	char	**my_paths;
	char	*cmd;
	char	*cmd_path;
	char	**cmd_args;

	if (access(input[0], X_OK) == 0)
		execve(input[0], &input[0], tab->envp);
	//path_envp = copy_new_line(getenv("PATH"));
	path_envp = get_path(tab);
	if (path_envp == NULL)
	{
		printf("bash: %s: No such file or directory\n", input[0]);
		exit(127);
	}
	my_paths = ft_split(path_envp, ':');
	i = 0;
	cmd_args = replace_quotes(input, tab);
	if (check_our_built_in(cmd_args, tab) == 0)
	{
		free_tab(cmd_args);
		exit(g_exit_status);
	}
	while (my_paths[i])
	{
		cmd_path = ft_strjoin(my_paths[i], "/");
		cmd = ft_strjoin(cmd_path, cmd_args[0]);
		execve(cmd, cmd_args, tab->envp);
		free_double(cmd, cmd_path);
		i++;
	}
	free_tab(cmd_args);
	exit(127);
}

int	check_cmd(char **tab_split, t_tab *tab)
{
	int	i;
	int	nb_pipe;

	i = 0;
	nb_pipe = 0;
	while (tab_split[nb_pipe])
		nb_pipe++;
	if (!tab_split[0])
		return (0);
	ft_pipe(tab_split, (nb_pipe - 1), i, tab);
	return (0);
}
