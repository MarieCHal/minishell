/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchalard <mchalard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 13:40:08 by mchalard          #+#    #+#             */
/*   Updated: 2022/06/26 15:52:19 by mchalard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*word_dup(const char *str, int start, int finish)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc((finish - start + 1) * sizeof(char));
	while (start < finish)
		word[i++] = str[start++];
	word[i] = '\0';
	return (word);
}

//--> counts words for ft_split
int	count_words(const char *str, char c)
{
	int	word;
	int	i;
	int	trigger;

	i = 0;
	trigger = 0;
	word = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			if ((i = ft_quotes(str, i, str[i])) == 0)
				return (0);
		}
		if (str[i] != c && trigger == 0)
		{
			trigger = 1;
			word++;
		}
		else if (str[i] == c)
			trigger = 0;
		i++;
	}
	return (word);
}

void	ft_init_split_struct(t_split *split, char const *s, char c)
{
	split->i = 0;
	split->j = 0;
	split->index = -1;
	split->check = count_words(s, c);
}

char	**ft_split(char const *s, char c)
{
	t_split count;
	char	**split;

	ft_init_split_struct(&count, s, c);
	split = malloc((count.check + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	while (count.i <= ft_strlen(s))
	{
		if (s[count.i] != c && count.index < 0)
			count.index = count.i;
		if (s[count.i] == '\'' || s[count.i] == '\"')
			count.i = ft_count_quotes(s, count.i, s[count.i]);
		else if ((s[count.i] == c || count.i == ft_strlen(s)) 
		&& count.index >= 0 && count.check > 0)
		{
			split[count.j++] = word_dup(s, count.index, count.i);
			count.index = -1;
			count.check--;
		}
		count.i++;
	}
	split[count.j] = 0;
	return (split);
}

//2.ft_split --> splits line per line the char ** returned by
/*char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	int		index;
	int		check_words;
	char	**split;

	check_words = count_words(s, c);
	split = malloc((check_words + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	i = 0;
	j = 0;
	index = -1;
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && index < 0)
			index = i;
		if (s[i] == '\'' || s[i] == '\"')
			i = ft_count_quotes(s, i, s[i]);
		else if ((s[i] == c || i == ft_strlen(s)) && index >= 0)
		{
			if (check_words > 0)
			{
				split[j++] = word_dup(s, index, i);
				index = -1;
				check_words--;
			}
		}
		i++;
	}
	split[j] = 0;
	return (split);
}*/
