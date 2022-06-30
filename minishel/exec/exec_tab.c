/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchalard <mchalard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 16:41:47 by mchalard          #+#    #+#             */
/*   Updated: 2022/06/30 16:22:24 by mchalard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_path(t_tab *tab)
{
	int		i;
	int		len;
	int		p;
	char	*path;

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
			return (path);
		}
		i++;
	}
	return (NULL);
}

void	ft_envp_path(char **input, t_tab *tab, t_exec *exec)
{
	exec->path_envp = get_path(tab);
	if (exec->path_envp == NULL)
	{
		printf("bash: %s: No such file or directory\n", input[0]);
		exit(127);
	}
	exec->my_paths = ft_split(exec->path_envp, ':');
	exec->cmd_args = replace_quotes(input, tab);
	if (access(exec->cmd_args[0], X_OK) == 0)
		execve(exec->cmd_args[0], &exec->cmd_args[0], tab->envp);
}

void	ft_init_exec(t_exec *exec)
{
	exec->path_envp = NULL;
	exec->my_paths = NULL;
	exec->cmd = NULL;
	exec->cmd_path = NULL;
	exec->cmd_args = NULL;
}

int	ft_execve(char **input, t_tab *tab)
{
	int		i;
	t_exec	exec;

	ft_envp_path(input, tab, &exec);
	i = 0;
	if (check_our_built_in(exec.cmd_args, tab) == 0)
	{
		free_tab(exec.cmd_args);
		exit(g_exit_status);
	}
	while (exec.my_paths[i])
	{
		exec.cmd_path = ft_strjoin(exec.my_paths[i], "/");
		exec.cmd = ft_strjoin(exec.cmd_path, exec.cmd_args[0]);
		execve(exec.cmd, exec.cmd_args, tab->envp);
		free_double(exec.cmd, exec.cmd_path);
		i++;
	}
	free_tab(exec.cmd_args);
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
