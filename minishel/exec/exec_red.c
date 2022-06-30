/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_red.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchalard <mchalard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 14:23:05 by mchalard          #+#    #+#             */
/*   Updated: 2022/06/30 15:20:16 by mchalard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_heredoc_tab(t_fd *files)
{
	int	j;

	j = 0;
	if (files->heredocs == 1 && files->tab_in != NULL)
	{
		while (files->tab_in[j])
		{
			printf("%s\n", files->tab_in[j]);
			j++;
		}
	}
}

void	ft_wait(t_fd *files, t_pid *pid)
{
	int	status;

	status = 0;
	close_fd(files);
	waitpid(pid->pid_child1, NULL, 0);
	waitpid(pid->pid_child2, &status, 0);
	g_exit_status = WEXITSTATUS(status);
}

void	ft_init_pid(t_pid *pid)
{
	pipe(pid->fd);
	pid->pid_child1 = fork();
	pid->pid_child2 = fork();
}

int	exec_red(char **cmd, t_fd *files, t_tab *tab)
{
	t_pid	pid;

	ft_init_pid(&pid);
	if (pid.pid_child1 == 0)
	{
		dup2(pid.fd[1], STDOUT_FILENO);
		close_pipes(1, &pid.fd);
		check_heredoc_tab(files);
		exit(0);
	}
	if (pid.pid_child2 == 0)
	{
		if (files->fd_in != -1 && files->heredocs == 0)
			dup2(files->fd_in, STDIN_FILENO);
		if (files->heredocs == 1)
			dup2(pid.fd[0], STDIN_FILENO);
		if (files->fd_out != -1)
			dup2(files->fd_out, STDOUT_FILENO);
		close_pipes(1, &pid.fd);
		ft_execve(cmd, tab);
	}
	close_pipes(1, &pid.fd);
	ft_wait(files, &pid);
	return (0);
}
