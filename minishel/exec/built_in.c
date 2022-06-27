/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchalard <mchalard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 11:13:57 by mchalard          #+#    #+#             */
/*   Updated: 2022/06/27 15:47:03 by mchalard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// checks if the command is a built_in command of our shell
//NO LEAKS IN BUIL_IN FUNCTION !!!!!
int	built_in(char *command)
{
	DIR				*dir;
	const char		*args;
	const char		*com;
	struct dirent	*dent;
	int				i;

	i = 0;
	args = "/Users/mchalard/Desktop/rank 03/minishel/built_in";
	dir = opendir(args);
	if (dir == NULL)
		printf("errordir\n");
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

int    check_our_built_in(char **tab1, t_tab *tab)
{
    int     i;
    
    if (!(i = built_in (tab1[0])))
        return (1);
    else
    {
        if (i == 2)
            ft_cd(tab1[1], tab);
        if (i == 4)
            ft_echo(tab1);
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
    return (0);
}
