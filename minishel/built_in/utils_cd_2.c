/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cd_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeauman <gbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 16:31:48 by gbeauman          #+#    #+#             */
/*   Updated: 2022/06/29 16:40:20 by gbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../minishell.h"

char	*new_path_malloc(char *path, char *new_path)
{
	int	len;
	int	i;
	int	j;

	len = ft_strlen(path);
	i = 2;
	new_path = malloc ((len - 2) * sizeof(char));
	j = 0;
	while (path[i])
	{
		new_path[j++] = path[i];
		i++;
	}
	new_path[j] = '\0';
	free (path);
	i = 0;
	path = malloc ((len - 2) * sizeof(char));
	while (new_path[i])
	{
		path[i] = new_path[i];
		i++;
	}
	path[i] = '\0';
	free (new_path);
	return (path);
}

void	cd_home(t_tab *tab, int j)
{
	ft_is_oldpwd(tab, j + 1);
	free (tab->envp[j]);
	tab->envp[j] = ft_strjoin(tab->pwd_var, tab->home_path);
	chdir (tab->home_path);
}
