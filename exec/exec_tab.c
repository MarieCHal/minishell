/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchalard <mchalard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 15:16:34 by mchalard          #+#    #+#             */
/*   Updated: 2022/05/19 11:46:05 by mchalard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// checks if the command is a built_in command of our shell
int built_in(char *command)
{
    DIR *dir;
    const char *args;
    const char    *com;
    struct dirent *dent;
    int             i;
    
    i = 0;
    args = "built_in";
    dir = opendir(args);
    if (dir == NULL)
        printf("error\n");
    while ((dent = readdir(dir)) != NULL)
    {
        com = dent->d_name;
        if (ft_strncmp(command, com, ft_strlen(command)) == 0)
            return (i);
        i++;
    }
    return (0);
}

//execute the command if it is in our built in
int    check_our_built_in(char **tab)
{
    int     i;
    
    if (!(i = built_in (tab[0])))
        return (0);
    else
    {
        if (i == 2)
            ft_cd(tab[1]);
        if (i == 4)
            ft_echo(tab);
        if (i == 8)
            ft_exit();
        if (i == 12)
            ft_pwd();
    }
    return (1);
}

//checks if the comand is a built in shell command
int check_built_in_shell(char **tab)
{
    char    *path_exec;
    char    *envp[] = {"OLDPWD", NULL};
    char    **argv;
    int     j;
    
    j = 0;
    while (tab[j])
        j++;
    argv = malloc(j + 1 * sizeof(char *));
    j = 0;
    while (tab[j])
    {
        argv[j] = malloc(sizeof(char) *ft_strlen(tab[j]));
        argv[j] = tab[j];
        j++;
    }
    argv[j] = NULL;    
    path_exec = ft_strjoin("/bin/", tab[0]);
    if ((execve(path_exec, argv, envp) == -1))
    {
        printf("error\n");
        return (0);
    }
    free_tab(argv);
    return (0);
}

//checks if the command is a shell command
int check_cmd_shell(char **tab)
{
    char    *path_exec;
    char    *envp[] = {getenv("OLDPWD"), NULL};
    char    **argv;
    int     j;
    
    j = 0;
    while (tab[j])
        j++;
    argv = malloc(j + 1 * sizeof(char *));
    j = 0;
    while (tab[j])
    {
        argv[j] = malloc(sizeof(char) *ft_strlen(tab[j]));
        argv[j] = tab[j];
        j++;
    }
    argv[j] = NULL;
    path_exec = ft_strjoin("/usr/bin/", tab[0]);
    if (execve(path_exec, argv, envp) == -1)
    {
        printf("error\n");
        return (0);
    }
    free_tab(argv);
    return (0);
}

//checks command (first line of tab1)
int    check_cmd(char **tab)
{
    int i;

    i = 0;
    if (!(i = check_our_built_in(tab)))
    {
        if (!(check_built_in_shell(tab)))
        {
            if (!(check_cmd_shell(tab)))
                return (0);
        }
    }
    return (1);
}