/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pid.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchalard <mchalard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 14:22:52 by mchalard          #+#    #+#             */
/*   Updated: 2022/05/20 13:28:51 by mchalard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int sig_trigger(char c)
{
    static int n = 0;
    
    if (c == 's')
        n++;
    return (n);
}

void    sig_int()
{
    char    *path_exec;
    char    *envp[] = {getenv("PWD"), NULL};
    char    *argv[] = {"minishell", NULL};

    printf("ok\n");
    signal(SIGINT, sig_int);
    path_exec = ft_strjoin(getenv("PWD"), "/minishell");
    printf("%s\n", path_exec);
    execve(path_exec, argv, envp);
}

void    sig_segv()
{
    exit(0);
}

/*int  main(void)
{
    signal(SIGINT, sig_int);
    //signal(SIGINT, sig_int);
	signal(SIGSEGV, sig_segv);
	//signal(SIGQUIT, sig_quit);
    while (1)
    {
        printf("salut\n");
        sleep(1);
    }
    return (0);
}*/