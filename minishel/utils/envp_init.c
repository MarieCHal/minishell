/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchalard <mchalard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 13:35:40 by mchalard          #+#    #+#             */
/*   Updated: 2022/06/27 13:36:02 by mchalard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
