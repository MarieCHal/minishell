/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchalard <mchalard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 16:41:47 by mchalard          #+#    #+#             */
/*   Updated: 2022/06/15 14:57:03 by mchalard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_execve(char *input)
{
    int     i;
    char    *path_envp;
    char    **my_paths;
    char    **cmd_args;
    char    **cmd_split;
    char    *cmd;
    char    *cmd_path;
    
    path_envp = copy_new_line("/Users/mchalard/.brew/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki:/Library/Apple/usr/bin:/Users/mchalard/.brew/bin");
    my_paths = ft_split(path_envp, ':');
    cmd_split = ft_split(input, ' ');
    cmd_args = parsed_tab(cmd_split);
    free_tab(cmd_split);
    i = 0;
    check_our_built_in(cmd_args);
    while (my_paths[i])
    {
        cmd_path = ft_strjoin(my_paths[i], "/");
        cmd = ft_strjoin(cmd_path, cmd_args[0]);
        execve(cmd, cmd_args, NULL);
        free(cmd);
        free(cmd_path);
        i++;
    }
    printf("bash: %s: command not found\n", cmd_args[0]);
    exit(0);
}

int ft_new_execve(char **input)
{
    int     i;
    char    *path_envp;
    char    **my_paths;
    //char    **cmd_args;
    //char    **cmd_split;
    char    *cmd;
    char    *cmd_path;
    
    path_envp = copy_new_line("/Users/mchalard/.brew/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki:/Library/Apple/usr/bin:/Users/mchalard/.brew/bin");
    my_paths = ft_split(path_envp, ':');
    //cmd_split = ft_split(input, ' ');
    //cmd_args = parsed_tab(cmd_split);
    //free_tab(cmd_split);
    i = 0;
    check_our_built_in(input);
    while (my_paths[i])
    {
        cmd_path = ft_strjoin(my_paths[i], "/");
        cmd = ft_strjoin(cmd_path, input[0]);
        execve(cmd, input, NULL);
        free(cmd);
        free(cmd_path);
        i++;
    }
    printf("bash: %s: command not found\n", input[0]);
    exit(0);
}

int    check_cmd(char **tab_split)
{
    int i;
    int nb_pipe;
    
    i = 0;
    nb_pipe = 0;
    while (tab_split[nb_pipe])
        nb_pipe++;
    if (!tab_split[0])
        return(0);
    ft_pipe(tab_split, (nb_pipe - 1));
    return (0);
}