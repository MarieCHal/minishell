/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_parse_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchalard <mchalard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 14:36:35 by mchalard          #+#    #+#             */
/*   Updated: 2022/06/27 15:12:35 by mchalard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//NO LEAKS!!!!!!

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

//manage the single quotes
void	manage_single_quote(t_count *count, char *line)
{
	char	*tmp;
	char	*stock;

	count->j = 0;
	count->i++;
	tmp = malloc(sizeof(char) * mem_single_quote(line, count->i) + 1);
	stock = stock_quotes(count);
	while (line[count->i] != '\'')
		tmp[count->j++] = line[count->i++];
	tmp[count->j] = '\0';
	count->i++;
	count->new_line = ft_strjoin_line(stock, tmp);
	free_double(stock, tmp);
}

//manage double quotes
void	manage_double_quotes(t_count *count, char *line, t_tab *tab)
{
	char	*tmp;
	char	*stock;

	count->j = 0;
	count->i++;
	tmp = malloc(sizeof(char) * mem_double_quotes(line, count->i, tab) + 1);
	stock = stock_quotes(count);
	while (line[count->i] != '\"')
	{
		if (line[count->i] == '$')
		{
			if (check_dollar_lenght(count->i, line) > 0)
				manage_dollar(count, tmp, line, tab);
			else
				tmp[count->j++] = line[count->i++];
		}
		else if ((line[count->i] != '$') && (line[count->i] != '\"')
			&& (line[count->i] != '\0'))
			tmp[count->j++] = line[count->i++];
	}
	tmp[count->j] = '\0';
	count->new_line = ft_strjoin_line(stock, tmp);
	free_double(stock, tmp);
	count->i++;
}

//manage no quotes
void	no_quotes(t_count *count, char *line, t_tab *tab)
{
	char	*tmp;
	char	*stock;

	count->j = 0;
	tmp = malloc(sizeof(char) * mem_no_quotes(line, count->i, tab) + 1);
	stock = stock_quotes(count);
	while ((line[count->i] != '\'') && (line[count->i] != '\"')
		&& (line[count->i] != '\0'))
	{
		if (line[count->i] == '$' && check_dollar_lenght(count->i, line) > 0)
			manage_dollar(count, tmp, line, tab);
		else
			tmp[count->j++] = line[count->i++];
	}
	tmp[count->j] = '\0';
	count->new_line = ft_strjoin_line(stock, tmp);
	free_double(stock, tmp);
}

//checks the quotes and direct to the dollar function depending on th settings
char	*check_quotes(char *line, t_tab *tab)
{
	t_count	count;

	count.i = 0;
	count.j = 0;
	count.k = 0;
	count.new_line = NULL;
	while (line[count.i] != '\0')
	{
		if (line[count.i] == '\'')
			manage_single_quote(&count, line);
		if (line[count.i] == '\"')
			manage_double_quotes(&count, line, tab);
		if ((line[count.i] != '\'') && (line[count.i] != '\"')
			&& (line[count.i] != '\0'))
			no_quotes(&count, line, tab);
	}
	return (count.new_line);
}
