/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeauman <gbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 18:13:06 by mchalard          #+#    #+#             */
/*   Updated: 2022/06/29 15:01:39 by gbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_echo(char **tab)
{
	int	j;

	j = 1;
	while (tab[j])
	{
		printf("%s", tab[j]);
		printf(" ");
		j++;
	}
	printf("\n");
	return (exit_status = 0);
}
