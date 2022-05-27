/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeauman <gbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 18:49:25 by mchalard          #+#    #+#             */
/*   Updated: 2022/05/27 14:21:17 by gbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_cd(char *path, t_tab *tab)
{
	int			j;
	int			i;
	int			i2;
	int			len;
	char		*slash_path;
	char		*just_path;
	char		*old_path;
	char		*stock_pwd;
	char		*back_dir;
	static int	trigger = 0;

    j = 0;
	i = 3;
	i2 = 0;
	back_dir = NULL;
	while (tab->envp[j])
	{
		if (ft_strncmp(tab->envp[j], "PWD", 3) == 0)
		{
			len = ft_strlen(tab->envp[j]);
			just_path = malloc((len - 2) * sizeof(char));
			while (tab->envp[j][i] && tab->envp[j][i + 1] != '.')
			{
				just_path[i2] = tab->envp[j][i];
				i2++;
				i++;
			}
			just_path[i2] = '\0';
			if (ft_strncmp(path, "..", 2) == 0)
			{
				i =0;
				while (just_path[i2] != '/')
					i2--;
				i2--;
				back_dir = malloc(i2 + 2 * sizeof(char));
				while (i <= i2)
				{
					back_dir[i] = just_path[i];
					i++;
				}
				back_dir[i] = '\0';
				tab->envp[j] = ft_strjoin(tab->pwd_var, back_dir);
				free (back_dir);
			}
			else if (ft_strncmp(path, "..", 2) != 0)
			{
				slash_path = ft_strjoin("/", path);
				stock_pwd = ft_strjoin(tab->pwd_var, just_path);
				tab->envp[j] = ft_strjoin(stock_pwd, slash_path);
				if (trigger == 0)
					tab->envp[j + 1] = ft_strjoin(tab->oldpwd_var, just_path);
			}
		}
		else if (ft_strncmp(tab->envp[j], "OLDPWD", 6) == 0 && trigger == 1)
		{
			old_path = ft_strjoin(tab->oldpwd_var, just_path);
			tab->envp[j] = old_path;
		}
        j++;
    }
	trigger = 1;
	free (just_path);
	free (stock_pwd);
    tab->dir = slash_path;
    chdir(path);
}
