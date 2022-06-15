/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeauman <gbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 13:20:j by mchalard          #+#    #+#             */
/*   Updated: 2022/06/14 10:57:30 by gbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pwd_pos(t_tab *tab)
{
	int	j;

	j = 0;
	while (ft_strncmp(tab->envp[j], "PWD", 3) != 0)
		j++;
	return (j);
}

void	*ft_pwd(t_tab *tab)
{
	char	*pwd;
	int		i;
	int		j;
	int		len;

	i = 0;
	j = pwd_pos(tab);
	len = ft_strlen(tab->envp[j]) - 4;
	pwd = malloc(len + 1 * sizeof(char));
	while (tab->envp[j][i + 4])
	{
		pwd[i] = tab->envp[j][i + 4];
		i++;
	}
	pwd[i] = '\0';
	printf ("%s\n", pwd);
	free (pwd);
	return (0);
}
