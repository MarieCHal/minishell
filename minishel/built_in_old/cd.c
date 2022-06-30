/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchalard <mchalard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 18:49:25 by mchalard          #+#    #+#             */
/*   Updated: 2022/06/30 16:08:35 by mchalard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_is_minus(t_tab *tab, int j, int i)
{
	int	len;

	len = ft_strlen(tab->envp[j + 1]);
	tab->another_oldpwd = fill_malloc(tab, j + 1, i, len - 6);
	printf ("%s\n", tab->another_oldpwd);
	ft_is_oldpwd(tab, j + 1);
	free (tab->envp[j]);
	tab->envp[j] = ft_strjoin(tab->pwd_var, tab->another_oldpwd);
	chdir (tab->another_oldpwd);
	free (tab->another_oldpwd);
}

void	ft_is_path(t_tab *tab, int j, char *path)
{
	char	*slash_path;
	char	*stock_pwd;

	slash_path = ft_strjoin("/", path);
	stock_pwd = ft_strjoin(tab->pwd_var, tab->just_path);
	tab->envp[j] = ft_strjoin(stock_pwd, slash_path);
	free (stock_pwd);
	free (slash_path);
}

void	ft_is_pwd(t_tab *tab, char *path, int j)
{
	int	len;
	int	i;

	i = 4;
	len = ft_strlen(tab->envp[j]);
	tab->just_path = fill_malloc(tab, j, i, len - 3);
	if (ft_strncmp(path, "..", 2) == 0)
		ft_is_back(tab, j);
	else
		ft_is_path(tab, j, path);
}

void	ft_correct_path(t_tab *tab, char *path)
{
	int	j;

	j = 0;
	while (tab->envp[j])
	{
		if (ft_strncmp(tab->envp[j], "PWD", 3) == 0)
			ft_is_pwd(tab, path, j);
		else if (ft_strncmp(tab->envp[j], "OLDPWD", 6) == 0)
			ft_is_oldpwd(tab, j);
		j++;
	}
}

int	ft_cd(char *path, t_tab *tab)
{
	int		i;
	int		j;

	i = 0;
	j = find_pwd_line(tab);
	if (path == NULL || (ft_strncmp(path, "~", 1) == 0))
	{
		ft_is_oldpwd(tab, j + 1);
		tab->envp[j] = ft_strjoin(tab->pwd_var, tab->home_path);
		chdir (tab->home_path);
	}
	else if (ft_strncmp(path, "-", 1) == 0)
		ft_is_minus(tab, j, i + 7);
	else if (chdir(path) != 0)
	{
		printf ("cd: %s: No such file or directory\n", path);
		return (1);
	}
	else if (ft_strncmp(path, "..", 2) == 0)
		ft_back_cd(tab, path, j, i);
	else if (chdir(path))
		ft_correct_path(tab, path);
	return (0);
}
