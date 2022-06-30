/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchalard <mchalard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 14:48:00 by mchalard          #+#    #+#             */
/*   Updated: 2022/06/30 15:36:41 by mchalard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_count_pipes(char *cmd_line, char **result)
{
	int	pipes;
	int	i;

	pipes = 0;
	i = 0;
	while (cmd_line[i])
	{
		if (cmd_line[i] == '|')
			pipes++;
		i++;
	}
	i = 0;
	while (result[i])
		i++;
	if (i != (pipes + 1))
	{
		free(cmd_line);
		free_tab(result);
		return (1);
	}
	return (0);
}

int	ft_count_red(char **str, char q)
{
	int	i;
	int	j;
	int	nb_red;

	i = 0;
	j = 0;
	nb_red = 0;
	while (str[j])
	{
		i = 0;
		while (str[j][i])
		{
			if (str[j][i] == '\'' || str[j][i] == '\"')
				i = ft_count_quotes(str[j], i, str[j][i]);
			if (str[j][i] == q)
			{
				if (str[j][i + 1] == q)
					i++;
				nb_red++;
			}
			i++;
		}
		j++;
	}
	return (nb_red);
}

int	words_count(char **str, char c1, char c2, t_pars *p)
{
	if (str[p->j][p->i] == '\'' || str[p->j][p->i] == '\"')
	{
		p->i = ft_quotes(str[p->j], p->i, str[p->j][p->i]);
		if (p->i == 0)
			return (0);
	}
	if (str[p->j][p->i] == c1 || str[p->j][p->i] == c2)
	{
		if (str[p->j][p->i] == str[p->j][p->i + 1])
			p->i++;
		p->word++;
	}
	p->i++;
	return (1);
}

int	count_words_red(char **str, char c1, char c2)
{
	t_pars	p;

	p.i = 0;
	p.j = 0;
	p.word = 0;
	while (str[p.j])
	{
		p.i = 0;
		while (str[p.j][p.i])
		{
			if (!words_count(str, c1, c2, &p))
				return (0);
		}
		p.word++;
		p.j++;
	}
	return (p.word);
}

int	ft_len_red(char *str, int start)
{
	int	i;
	int	len;

	i = start;
	len = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			len += ft_quotes(str, i, str[i]);
			i += ft_quotes(str, i, str[i]);
		}
		if (str[i] == '<' || str[i] == '>')
			return (len);
		len++;
		i++;
	}
	return (len);
}
