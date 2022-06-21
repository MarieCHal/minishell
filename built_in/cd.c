/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeauman <gbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 09:08:56 by gbeauman          #+#    #+#             */
/*   Updated: 2022/06/21 16:38:46 by gbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../minishell.h"

int	find_pwd_line(t_tab *tab);
void	ft_is_oldpwd(t_tab *tab, int j);

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
			break;
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

void	ft_is_oldpwd(t_tab *tab, int j)
{
	char	*old_path;

	old_path = ft_strjoin(tab->oldpwd_var, tab->just_path);
	tab->envp[j] = old_path;
}

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

void	ft_back_cd(t_tab *tab, char *path, int j, int i)
{
	char	**split_path;
	char	*back_oldpwd;
	
	split_path = ft_split(path, '/');
	back_oldpwd = tab->just_path;
	while (split_path[i])
	{
		ft_is_back(tab, j);
		find_pwd_line(tab);
		i++;
	}
	tab->envp[j + 1] = ft_strjoin(tab->oldpwd_var, back_oldpwd);
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

void	ft_cd(char *path, t_tab *tab)
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
		printf ("cd: %s: No such file or directory\n", path);
	else if (ft_strncmp(path, "..", 2) == 0)
		ft_back_cd(tab, path, j, i);
	else if (chdir(path))
		ft_correct_path(tab, path);
}
