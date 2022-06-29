/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchalard <mchalard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 16:42:52 by mchalard          #+#    #+#             */
/*   Updated: 2022/06/29 16:51:15 by mchalard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_error_nb_quotes(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\'' || cmd[i] == '\"')
		{
			i = ft_quotes(cmd, i, cmd[i]);
			if (i == 0)
			{
				free(cmd);
				return (0);
			}
		}
		i++;
	}
	return (1);
}

int	ft_quotes(const char *str, int i, char q)
{
	i++;
	while (str[i] != q && str[i])
		i++;
	if (str[i] == '\0')
	{
		printf("error --------- quotes\n");
		return (0);
	}
	return (i);
}

int	ft_count_quotes(const char *str, int i, char q)
{
	i++;
	while (str[i] != q)
		i++;
	return (i);
}

char	*stock_quotes(t_count *count)
{
	char	*stock;

	if (count->new_line != 0)
	{
		stock = copy_new_line(count->new_line);
		free(count->new_line);
	}
	else
		stock = NULL;
	return (stock);
}
