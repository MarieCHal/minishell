/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchalard <mchalard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 13:20:12 by mchalard          #+#    #+#             */
/*   Updated: 2022/06/27 14:29:53 by mchalard         ###   ########.fr       */
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

int	ft_pwd(t_tab *tab)
{
	char	*pwd;
	int		i;
	int		j;
	int		len;

	i = 0;
	j = pwd_pos(tab);
	len = ft_strlen(tab->envp[j]) - 4;
	pwd = malloc(len + 1 * sizeof(char));
	if (!pwd)
		return (1);
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
