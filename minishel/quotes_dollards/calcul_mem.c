/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcul_mem.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchalard <mchalard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 15:32:19 by mchalard          #+#    #+#             */
/*   Updated: 2022/06/27 15:11:12 by mchalard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	mem_no_quotes(char *line, int pos, t_tab *tab)
{
	int	size;

	size = 0;
	while ((line[pos] != '\'') && (line[pos] != '\"') && (line[pos] != '\0'))
	{
		if (line[pos] == '$' && (check_dollar_lenght(pos, line)) > 0)
		{
			if (check_dollar(pos, line, tab) != 0)
				size += ft_strlen(check_dollar(pos, line, tab));
			pos += check_dollar_lenght(pos, line);
			pos++;
		}
		else
		{
			size++;
			pos++;
		}
	}
	return (size);
}

int	mem_double_quotes(char *line, int pos, t_tab *tab)
{
	int	size;

	size = 0;
	while (line[pos] != '\"')
	{
		if (line[pos] == '$' && (check_dollar_lenght(pos, line)) > 0)
		{
			if (check_dollar(pos, line, tab) != 0)
				size += ft_strlen(check_dollar(pos, line, tab));
			pos += check_dollar_lenght(pos, line);
			pos++;
		}
		else if ((line[pos] != '\"') && (line[pos] != '\0'))
		{
			size++;
			pos++;
		}
	}
	return (size);
}

int	mem_single_quote(char *line, int pos)
{
	int	size;

	size = 0;
	while (line[pos] != '\'' && line[pos] != '\0')
	{
		size++;
		pos++;
	}
	return (size);
}
