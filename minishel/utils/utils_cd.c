/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchalard <mchalard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 13:32:41 by mchalard          #+#    #+#             */
/*   Updated: 2022/06/29 13:26:16 by mchalard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	find_pwd_line(t_tab *tab)
{
	int	j;
	int	i;
	int	len;

	j = 0;
	i = 4;
	while (ft_strncmp(tab->envp[j], "PWD", 3) != 0)
		j++;
	len = ft_strlen(tab->envp[j]);
	tab->just_path = fill_malloc(tab, j, i, len - 3);
	return (j);
}

void	ft_is_oldpwd(t_tab *tab, int j)
{
	free (tab->envp[j]);
	tab->envp[j] = ft_strjoin(tab->oldpwd_var, tab->just_path);
}

char	*fill_malloc(t_tab *tab, int j, int i, int len)
{
	char	*str;
	int		i2;

	i2 = 0;
	str = malloc (len * sizeof (char));
	while (tab->envp[j][i])
	{
		str[i2] = tab->envp[j][i];
		i2++;
		i++;
	}
	str[i2] = '\0';
	return (str);
}

void	ft_back_cd(t_tab *tab, char *path, int j, int i)
{
	char	**split_path;
	char	*back_oldpwd;

	split_path = ft_split(path, '/');
	back_oldpwd = tab->just_path;
	while (split_path[i])
	{
		ft_is_back(tab, j);
		free (tab->just_path);
		find_pwd_line(tab);
		i++;
	}
	free (tab->envp[j + 1]);
	tab->envp[j + 1] = ft_strjoin(tab->oldpwd_var, back_oldpwd);
	free_tab (split_path);
}

void	ft_is_back(t_tab *tab, int j)
{
	int		i;
	int		i2;
	char	*back_dir;

	i = 0;
	i2 = 0;
	while (tab->just_path[i2])
		i2++;
	while (tab->just_path[i2] != '/')
	{
		if (i2 == 1)
			break ;
		else
			i2--;
	}
	back_dir = malloc(i2 + 1 * sizeof(char));
	while (i < i2)
	{
		back_dir[i] = tab->just_path[i];
		i++;
	}
	back_dir[i] = '\0';
	free (tab->envp[j]);
	tab->envp[j] = ft_strjoin(tab->pwd_var, back_dir);
	free (back_dir);
}