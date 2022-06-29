/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchalard <mchalard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 18:31:27 by mchalard          #+#    #+#             */
/*   Updated: 2022/06/29 10:29:49 by mchalard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exit_check_args(char **tab)
{
	int	i;

	i = 0;
	while (tab[1][i])
	{
		if (tab[1][i] < 48 || tab[1][i] > 57)
		{
			printf("exit: %s: numeric argument required\n", tab[1]);
			exit(255);
		}
		i++;
	}
	exit (ft_atoi(tab[1]));
}

int	ft_exit(char **tab)
{
	int	j;

	j = 0;
	while (tab[j])
		j++;
	if (j > 2)
	{
		printf("exit: too many arguments\n");
		return (g_exit_status = 1);
	}
	else if (j == 2)
		ft_exit_check_args(tab);
	else
		exit(0);
	return (g_exit_status = 1);
}
