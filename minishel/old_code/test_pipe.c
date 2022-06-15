/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchalard <mchalard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 11:01:59 by mchalard          #+#    #+#             */
/*   Updated: 2022/06/02 10:12:47 by mchalard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

//eseier way to execve
int ft_execve(char *input)
{
    int     i;
    char    *path_envp;
    char    **my_paths;
    char    **cmd_args;
    char    *cmd;
    char    *cmd_path;
    
    path_envp = copy_new_line("/Users/mchalard/.brew/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki:/Library/Apple/usr/bin:/Users/mchalard/.brew/bin");
    my_paths = ft_split_pipe(path_envp, ':');
    cmd_args = ft_split_pipe(input, ' ');
    i = 0;
    while (my_paths[i])
    {
        cmd_path = ft_strjoin(my_paths[i], "/");
        cmd = ft_strjoin(cmd_path, cmd_args[0]);
        execve(cmd, cmd_args, NULL);
        free(cmd);
        free(cmd_path);
        i++;
    }
    return(EXIT_FAILURE);
}

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


int main(void)
{
    char **cmd;
    int  nb_pipe;

    cmd = ft_split("cat test_pipe.c|grep printf", '|');
    nb_pipe = 0;
    while (cmd[nb_pipe])
    {
        printf("cmd %d: %s\n", nb_pipe, cmd[nb_pipe]);
        nb_pipe++;
    }
    printf("result: \n");
    ft_pipe(cmd, nb_pipe - 1);
    return(0);
}