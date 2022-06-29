/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_free_close.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeauman <gbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 16:41:41 by mchalard          #+#    #+#             */
/*   Updated: 2022/06/28 13:43:51 by gbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_tab(char **tab_to_free)
{
	int	j;

	j = 0;
	if (tab_to_free != NULL)
	{
		while (tab_to_free[j])
		{
			free(tab_to_free[j]);
			j++;
		}
		free(tab_to_free);
	}
}

void	free_double(char *stock, char *tmp)
{
	if (stock != 0)
        free(stock);
    if (tmp != 0)
        free(tmp);
}

char	*mymalloc(const char *s, size_t len)
{
	char	*cpy;

	if (len < ft_strlen(s))
		cpy = malloc(len * sizeof(char) + 1);
	else
		cpy = malloc(ft_strlen(s) * sizeof(char) + 1);
	return (cpy);
}

char	*copy_new_line(char *new_line)
{
	char	*stock;
	int		i;

	i = 0;
	stock = malloc(sizeof(char) * ft_strlen(new_line) + 1);
	while (new_line[i] != '\0')
	{
		stock[i] = new_line[i];
		i++;
	}
	stock[i] = '\0';
	return (stock);
}