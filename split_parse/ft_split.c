/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchalard <mchalard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 13:40:08 by mchalard          #+#    #+#             */
/*   Updated: 2022/05/17 15:51:06 by mchalard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//--> ? maybe not necessary (libft/utils) ?
size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != 0)
		i++;
	return (i);
}


static char	*word_dup(const char *str, int start, int finish)
{
	//printf("word dup\n");
	char	*word;
	int		i;

	i = 0;
	word = malloc((finish - start + 1) * sizeof(char));
	while (start < finish)
		word[i++] = str[start++];
	word[i] = '\0';
	return (word);
}

static char	*word_dup_pipe(const char *str, int start, int finish)
{
	//printf("word dup pipe\n");
	char	*word;
	int		i;

	i = 0;
	word = malloc((finish - start + 1) * sizeof(char));
	while (start < finish)
		word[i++] = str[start++];
	word[i - 1] = '\0';
	return (word);
}


//-->counts words for ft_split_pipe
static int	pipe_count_words(const char *str, char c)
{
	int	i;
	int	trigger;

	i = 0;
	trigger = 0;
	while (*str)
	{
		if (*str != c && trigger == 0)
		{
			trigger = 1;
			i++;
		}
		else if (*str == c)
			trigger = 0;
		str++;
	}
	return (i);
}

int	check_pipe_split(const char *str, int i)
{
	while (str[i])
	{
		if (str[i] == '|')
			return (1);
		else if (str[i] == ' ' && str[i + 1] == '\0')
			return (1);
		i++;
	}
	return (0);
}

//1.ft_split_pipe --> splits the argument according to the pipes
char	**ft_split_pipe(char const *s, char c)
{
	size_t	i;
	size_t	j;
	int		index;
	char	**split;

	split = malloc((pipe_count_words(s, c) + 1) * sizeof(char *));
	if (!s || !split)
		return (0);
	i = 0;
	j = 0;
	index = -1;
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && index < 0)
			index = i;
		else if ((s[i] == c || i == ft_strlen(s)) && index >= 0)
		{
			if (!check_pipe_split(s, i - 1))
				split[j++] = word_dup(s, index, i);
			else
				split[j++] = word_dup_pipe(s, index, i);
			index = -1;
		}
		i++;
	}
	split[j] = 0;
	return (split);
}

//--> counts words for ft_split
static int	count_words(const char *str, char c)
{
	int	word;
    int i;
	int	trigger;
    int quote;

	i = 0;
    quote = 0;
	trigger = 0;
    word = 0;
	while (str[i])
	{
        if (str[i] == '\'' || str[i] == '\"')
        {
            if ((i = ft_quotes(str, i, str[i])) == 0)
                return (0);
            quote++;
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

//2.ft_split --> splits line per line the char ** returned by
// ft_split_pipe according to the spaces between the words
char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	int		index;
	char	**split;

	split = malloc((count_words(s, c) + 1) * sizeof(char *));
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
        {
            word_dup(s, i, ft_count_quotes(s, i, s[i]));
            i = ft_count_quotes(s, i, s[i]);
        }
		else if ((s[i] == c || i == ft_strlen(s)) && index >= 0)
		{
			split[j++] = word_dup(s, index, i);
			index = -1;
		}
		i++;
	}
	split[j] = 0;
	return (split);
}
