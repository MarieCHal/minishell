/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_tab1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeauman <gbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 15:16:34 by mchalard          #+#    #+#             */
/*   Updated: 2022/06/21 18:20:33 by gbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// checks if the command is a built_in command of our shell
int    check_our_built_in(char **tab1, t_tab *tab)
{
    int     i;
    
    if (!(i = built_in (tab1[0])))
        return (0);
    else
    {
        if (i == 2)
            ft_cd(tab1[1], tab);
        if (i == 4)
            ft_echo(tab1[1]);
        if (i == 6)
            ft_get_env(tab);
        if (i == 8)
            ft_exit();
        if (i == 10)
            ft_export(tab, tab1);
        if (i == 12)
            ft_pwd(tab);
		if (i == 14)
        	ft_unset(tab, tab1);
    }
    return (1);
}

//checks if the comand is a built in shell command
int check_built_in_shell(char **tab1)
{
    char    *path_exec;
    char    *envp[] = {"PWD", NULL};
    char    **argv;
    int     j;
    
    j = 0;
    while (tab1[j])
        j++;
    argv = malloc(j + 1 * sizeof(char *));
    j = 0;
    while (tab1[j])
    {
        argv[j] = malloc(sizeof(char) *ft_strlen(tab1[j]));
        argv[j] = tab1[j];
        j++;
    }
    argv[j] = NULL;    
    path_exec = ft_strjoin("/bin/", tab1[0]);
    if ((execve(path_exec, argv, envp) == -1))
    {
        printf("error2\n");
        return (0);
    }
    return (0);
}

//checks if the command is a shell command
int check_cmd_shell(char **tab1)
{
    char    *path_exec;
    char    *envp[] = {getenv("PWD"), NULL};
    char    **argv;
    int     j;
    
    j = 0;
    while (tab1[j])
        j++;
    argv = malloc(j + 1 * sizeof(char *));
    j = 0;
    while (tab1[j])
    {
        argv[j] = malloc(sizeof(char) *ft_strlen(tab1[j]));
        argv[j] = tab1[j];
        j++;
    }
    argv[j] = NULL;
    path_exec = ft_strjoin("/usr/bin/", tab1[0]);
    if (execve(path_exec, argv, envp) == -1)
    {
        printf("error3\n");
        return (0);
    }
    return (0);
}

//checks command (first line of tab1)
int    check_tab1(char **tab1, t_tab *tab)
{
    int i;

    i = 0;
    if (!(i = check_our_built_in(tab1, tab)))
    {
        if (!(check_built_in_shell(tab1)))
        {
            if (!(check_cmd_shell(tab1)))
                return (0);
        }
    }
    return (1);
}