/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchalard <mchalard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 14:48:38 by mchalard          #+#    #+#             */
/*   Updated: 2022/06/02 18:30:33 by mchalard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

//experience piping
/*int main(void)
{
    int fd[2];
    int id;
    char    input;
    char    result;
    
    input = 'c';
    if (pipe(fd) == -1)
        printf("error pipe\n");
    id = fork();
    if (id == 0)
    {
        close(fd[0]);
        write(fd[1], &input, 1);
        close(fd[1]);
    }
    else
    {
        close(fd[1]);
        read(fd[0], &result, 1);
        close(fd[0]);
        printf("result got from child process: %c\n", result);
    }
    return(0);
}*/

int	main(void)
{
	char	*cmd;
	
	//signal(SIGINT, sig_int);
	while (1)
	{
        cmd = readline("prompt> ");
        add_history(cmd);
        pipe_tab(cmd);
		free(cmd);
    }
	return (0);
}

/*//recreate the pipe operator
int main(void)
{
    int fd[2];
    int id;
    int pid1;
    int pid2;
    int file_output;
    int file2;
    
    id = pipe(fd);
    file_output = open("coucou.txt", O_WRONLY | O_CREAT, 0777);
    pid1 = fork();
    if (pid1 == 0)
    {
        //printf("ok cat");
        dup2(fd[0], STDIN_FILENO);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);
        execlp("cat", "cat", "main_pipe.c", NULL);            
    }
    pid2 = fork();
    if (pid2 == 0)
    {
        dup2(fd[0], STDIN_FILENO);
        //dup2(fd[1], STDOUT_FILENO);
        //file2 = dup2(file_output, STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);
        execlp("grep", "grep", "execlp", NULL);
    }
    close(fd[0]);
    close(fd[1]);
    close(file_output);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    return (0);
}
/*
int main(void)
{
    int fd[2];
    int id;
    int pid1;
    int pid2;
    int file_output;
    int file2;
    
    id = pipe(fd);
    file_output = open("coucou.txt", O_WRONLY | O_CREAT, 0777);
    pid1 = fork();
    if (pid1 == 0)
    {
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);
        execve("/bin/cat", "cat", "main_pipe.c", NULL);        
    }
    pid2 = fork();
    if (pid2 == 0)
    {
        dup2(fd[0], STDIN_FILENO);
        file2 = dup2(file_output, STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);
        execve("grep", "grep", "pipe", NULL);
    }
    close(fd[0]);
    close(fd[1]);
    close(file_output);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    return (0);
}*/