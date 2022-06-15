/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeauman <gbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 10:22:33 by gbeauman          #+#    #+#             */
/*   Updated: 2022/06/14 17:21:34 by gbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

void	envp_init(t_tab *tab, char **envp)
{
	int	i;
	int	i2;

	i = 0;
	i2 = 0;
	while (envp[i])
		i++;
	i++;
	tab->envp = malloc (i * sizeof(tab->envp));
	while (i2 < i - 1)
	{
		tab->envp[i2] = ft_strdup(envp[i2]);
		i2++;
	}
	tab->envp[i2] = NULL;
}