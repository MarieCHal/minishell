/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchalard <mchalard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 14:23:05 by mchalard          #+#    #+#             */
/*   Updated: 2022/06/16 15:31:20 by mchalard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*int ft_treat_heredoc(char **cmd, t_fd *files)
{
    int j;
    int pid1;
    int pid2;
    int fd[2];
    
    j = 0;
    pipe(fd);
    pid1 = fork();
    {
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);
        while (files->tab_in[j])
        {
            printf("%s\n", files->tab_in[j]);
            j++;
        }
        exit (0);
    }
    pid2 = fork();
    {
        dup2(fd[0], STDIN_FILENO);
        if (files->fd_out)
            dup2(files->fd_out, STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);
        ft_execve(cmd);
    }
    close(fd[0]);
    close(fd[1]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2,  NULL, 0);
    close_fd(files);
    return (0);    
}*/

int    test_red(char **cmd, t_fd *files)
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
    printf("pid_1 child: %d\n", pid_1);
    pid_2 = fork();
    if (pid_2 == 0)
    {
        if (files->fd_in && files->heredocs == 0)
            dup2(files->fd_in, STDIN_FILENO);
        if (files->heredocs == 1)
            dup2(fd[0], STDIN_FILENO);
        if (files->fd_out)
            dup2(files->fd_out, STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);
        ft_execve(cmd);
    }
    printf("pid_2 child: %d\n", pid_2);
    close(fd[0]);
    close(fd[1]);
    waitpid(pid_1, NULL, 0);
    waitpid(pid_2,  NULL, 0);
    close_fd(files);
    return (0);    
}
