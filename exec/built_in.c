/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchalard <mchalard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 11:13:57 by mchalard          #+#    #+#             */
/*   Updated: 2022/06/02 11:13:59 by mchalard         ###   ########.fr       */
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