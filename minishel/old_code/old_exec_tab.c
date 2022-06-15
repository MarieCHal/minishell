/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchalard <mchalard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 15:16:34 by mchalard          #+#    #+#             */
/*   Updated: 2022/05/25 14:36:52 by mchalard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// checks if the command is a built_in command of our shell
//NO LEAKS IN BUIL_IN FUNCTION !!!!!
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
        {
            closedir(dir);
            return (i);
        }
        i++;
    }
    closedir(dir);
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
    char    *envp[] = {NULL};
    char    **argv;
    pid_t   pid;
    int     wstatus;
    int     return_val;
    int     j;
    
    j = 0;
    pid = fork();
    if (pid < 0)
        printf("Error pid fork\n");
    while (tab[j])
        j++;
    argv = malloc(sizeof(char *) * j + 1);
    j = 0;
    while (tab[j])
    {
        argv[j] = copy_new_line(tab[j]);
        j++;
    }
    argv[j] = 0;
    path_exec = ft_strjoin("/bin/", tab[0]);
    if (pid == 0)
    {
        if ((execve(path_exec, argv, envp) == -1))
                exit(1);
    }
    else
    {
        waitpid(pid, &wstatus, 0);
        //printf("child1 finished\n");
        return_val = WEXITSTATUS(wstatus);
        free(path_exec);
        free_tab(argv);
        //printf("\n");
        //printf("child return val: %d\n", return_val);
        if (return_val == 0)
            return(1);
    }
    return (0);
}

//checks if the command is a shell command
int check_cmd_shell(char **tab)
{
    char    *path_exec;
    char    *envp[] = {NULL};
    char    **argv;
    pid_t   pid;
    int     wstatus;
    int     return_val;
    int     j;
    
    j = 0;
    pid = fork();
    if (pid < 0)
        printf("Error pid fork\n");
    while (tab[j])
        j++;
    //argv = malloc(j + 1 * sizeof(char *));
    argv = malloc(sizeof(char *) * j + 1);
    j = 0;
    while (tab[j])
    {
        argv[j] = copy_new_line(tab[j]);
        j++;
    }
    argv[j] = 0;
    path_exec = ft_strjoin("/usr/bin/", tab[0]);
    if (pid == 0)
    {
        if ((execve(path_exec, argv, envp) == -1))
            exit(1);
    }
    else
    {
        waitpid(pid, &wstatus, 0);
        //printf("child2 finished\n");
        return_val = WEXITSTATUS(wstatus);
        free(path_exec);
        free_tab(argv);
        //printf("\n");
        //printf("child return val: %d\n", return_val);
        if (return_val == 0)
            return(1);
    }
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