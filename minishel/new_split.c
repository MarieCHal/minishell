/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchalard <mchalard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 14:23:05 by mchalard          #+#    #+#             */
/*   Updated: 2022/06/15 14:59:26 by mchalard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//int 

void    close_fd(t_fd *files)
{
    if (files->heredocs == 1)
        free_tab(files->tab_in);
    if (files->fd_in != 0)
        close(files->fd_in);
    if (files->fd_out != 0)
        close(files->fd_out);  
}

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
        ft_new_execve(cmd);
    }
    close(fd[0]);
    close(fd[1]);
    waitpid(pid_1, NULL, 0);
    waitpid(pid_2,  NULL, 0);
    close_fd(files);
    return (0);    
}


int main(void)
{
    t_fd    files;
    char    *cmd;
    char    **split_pipe;
    char    **split_space1;
    char    **split_red;
    char    **post_fd;
    int     j;
    
    j = 0;
    files.append = 0;
    files.fd_in = 0;
    files.fd_out = 0;
    files.heredocs = 0;
    cmd = "cat << stop > test2.txt\0";
    split_pipe = ft_split(cmd, '|');
    while (split_pipe[j])
    {
        printf("split_pipe: %s\n", split_pipe[j]);
        j++;
    }
    j = 0;
    printf("split_pipe0[0]: %s\n", split_pipe[0]);
    split_space1 = ft_split(split_pipe[0], ' ');
    while (split_space1[j])
    {
        printf("split_spacce1: %s\n", split_space1[j]);
        j++;
    }
    j = 0;
    split_red = ft_parse_red(split_space1);
    while (split_red[j])
    {
        printf("split_red: %s\n" , split_red[j]);
        j++;
    }
    ft_check_fd_in(split_red, &files);
    post_fd = post_red(split_red);
    j = 0;
    while (post_fd[j])
    {
        printf("post_red: %s\n", post_fd[j]);
        j++;
    }
    test_red(post_fd, &files);
    return(0);
}