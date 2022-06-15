/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchalard <mchalard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 10:17:21 by mchalard          #+#    #+#             */
/*   Updated: 2022/06/02 18:05:39 by mchalard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_pipe(char **cmd, int nb_pipe)
{
    int i;
    int j;
    int fd[nb_pipe][2];
    int pid_child;
    
    i = 0;
    j = 0;
    while (i < nb_pipe)
    {
        pipe(fd[i]);
        i++;
    }
    i = 0;
    while (i <= nb_pipe)
    {
        pid_child = fork();
        if(pid_child == 0)
        {
            if (i > 0)
               dup2(fd[i - 1][0], STDIN_FILENO); 
            if (i < nb_pipe)
                dup2(fd[i][1], STDOUT_FILENO);    
            while(j < nb_pipe)
            {
                close(fd[j][0]);
                close(fd[j][1]);
                j++;
            }
            j = 0;
            ft_execve(cmd[i]);
        }
        i++;     
    }
    while(j < nb_pipe)
    {
        close(fd[j][0]);
        close(fd[j][1]);
        j++;
    }
    j = 0;
    waitpid(pid_child, NULL, 0);
    return (0);
}
