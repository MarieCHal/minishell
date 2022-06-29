/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeauman <gbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 14:26:17 by mchalard          #+#    #+#             */
/*   Updated: 2022/06/29 15:02:18 by gbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../minishell.h"

int	ft_get_env(t_tab *tab)
{
	int	j;
	int	i;
	int	trigger;

	j = 0;
	while (tab->envp[j])
	{
		trigger = 0;
		i = 0;
		while (tab->envp[j][i])
		{
			if (tab->envp[j][i] == '=')
			{
				trigger = 1;
				break ;
			}
			i++;
		}
		if (trigger == 1)
			printf("%s\n", tab->envp[j]);
		j++;
	}
	return (0);
}
