/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_red.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchalard <mchalard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 14:23:05 by mchalard          #+#    #+#             */
/*   Updated: 2022/06/17 14:44:44 by mchalard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int    exec_red(char **cmd, t_fd *files)
{
    int j;
    int pid_1;
    int pid_2;
    int fd[2];
    
    j = 0;
    pipe(fd);
    pid_1 = fork();
    if (pid_1 == 0)
    {
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);
        if (files->heredocs == 1)
        {
            while (files->tab_in[j])
            {
                printf("%s\n", files->tab_in[j]);
                j++;
            }
        }
        exit(0);
    }
    pid_2 = fork();
    if (pid_2 == 0)
    {
        if (files->fd_in != -1 && files->heredocs == 0)
            dup2(files->fd_in, STDIN_FILENO);
        if (files->heredocs == 1)
            dup2(fd[0], STDIN_FILENO);
        if (files->fd_out)
            dup2(files->fd_out, STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);
        ft_execve(cmd);
    }
    close(fd[0]);
    close(fd[1]);
    close_fd(files);
    waitpid(pid_1, NULL, 0);
    waitpid(pid_2,  NULL, 0);
    return (0);    
}
