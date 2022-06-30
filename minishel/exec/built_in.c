/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchalard <mchalard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 11:13:57 by mchalard          #+#    #+#             */
/*   Updated: 2022/06/30 16:08:19 by mchalard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// checks if the command is a built_in command of our shell
//NO LEAKS IN BUIL_IN FUNCTION !!!!!

char	*set_args_path(t_tab *tab, int i)
{
	int		len;
	int		p;
	char	*ret;
	char	*args;

	len = 0;
	p = 0;
	while (tab->envp[i][len])
		len++;
	args = malloc(sizeof(char) * (len - 4 + 1));
	len = 4;
	while (tab->envp[i][len])
		args[p++] = tab->envp[i][len++];
	args[p] = '\0';
	ret = ft_strjoin(args, tab->built_in);
	free (args);
	return (ret);
}

char	*find_args(t_tab *tab)
{
	int		i;
	char	*ret;

	i = 0;
	while (tab->envp[i])
	{
		if (ft_strncmp(tab->envp[i], "PWD=\0", 4) == 0)
		{
			ret = set_args_path(tab, i);
			return (ret);
		}
		i++;
	}
	return (NULL);
}

int	built_in(char *command, t_tab *tab)
{
	DIR				*dir;
	const char		*com;
	struct dirent	*dent;
	int				i;

	i = 0;
	dir = opendir(tab->args);
	if (dir == NULL)
		printf("error directory\n");
	dent = readdir(dir);
	while (dent != NULL)
	{
		com = dent->d_name;
		if (ft_strncmp(command, com, ft_strlen(command)) == 0)
		{
			closedir(dir);
			return (i);
		}
		i++;
		dent = readdir(dir);
	}
	closedir(dir);
	return (0);
}

int	check_our_built_in(char **tab1, t_tab *tab)
{
	int	i;

	i = built_in (tab1[0], tab);
	if (i == 0)
		return (1);
	else
	{
		if (i == 2)
			ft_cd(tab1[1], tab);
		if (i == 3)
			ft_echo(tab1);
		if (i == 4)
			ft_get_env(tab);
		if (i == 5)
			ft_exit(tab1);
		if (i == 6)
			ft_export(tab, tab1);
		if (i == 7)
			ft_pwd(tab);
		if (i == 8)
			ft_unset(tab, tab1);
	}
	return (0);
}
