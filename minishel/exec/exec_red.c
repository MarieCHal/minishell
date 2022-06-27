/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_red.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchalard <mchalard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 14:23:05 by mchalard          #+#    #+#             */
/*   Updated: 2022/06/27 13:57:35 by mchalard         ###   ########.fr       */
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

/*void    ft_wait(int fd[2], t_fd *files, int pid_1, int pid_2)
{
    int status;
    
    status = 0;
    close_pipes(1, &fd[2]);
    close_fd(files);
    waitpid(pid_1, NULL, 0);
    waitpid(pid_2,  &status, 0);
    exit_status = WEXITSTATUS(status);
}*/

int	exec_red(char **cmd, t_fd *files, t_tab *tab)
{
	int	pid_1;
	int	pid_2;
	int	fd[2];
	int	status;

	pipe(fd);
	pid_1 = fork();
	if (pid_1 == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close_pipes(1, &fd);
		check_heredoc_tab(files);
		exit(0);
	}
    //waitpid(pid_1, NULL, 0);
    pid_2 = fork();
    if (pid_2 == 0)
    {
        if (files->fd_in != -1 && files->heredocs == 0)
            dup2(files->fd_in, STDIN_FILENO);
        if (files->heredocs == 1)
            dup2(fd[0], STDIN_FILENO);
        if (files->fd_out != -1)
            dup2(files->fd_out, STDOUT_FILENO);
        close_pipes(1, &fd);
        ft_execve(cmd, tab);
    }
    //ft_wait(&fd[2], files, pid_1, pid_2);
    close_pipes(1, &fd);
    close_fd(files);
    waitpid(pid_1, NULL, 0);
    waitpid(pid_2,  &status, 0);
    exit_status = WEXITSTATUS(status);
    return (0);    
}
