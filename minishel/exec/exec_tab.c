/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchalard <mchalard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 16:41:47 by mchalard          #+#    #+#             */
/*   Updated: 2022/06/17 11:27:35 by mchalard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_execve(char **input)
{
    int     i;
    char    *path_envp;
    char    **my_paths;
    char    *cmd;
    char    *cmd_path;
    char    **cmd_args;
    
    path_envp = copy_new_line("/Users/mchalard/.brew/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki:/Library/Apple/usr/bin:/Users/mchalard/.brew/bin");
    my_paths = ft_split(path_envp, ':');
    i = 0;
    cmd_args = replace_quotes(input);
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