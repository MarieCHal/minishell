/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchalard <mchalard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 14:48:38 by mchalard          #+#    #+#             */
/*   Updated: 2022/05/24 15:18:27 by mchalard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
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
}