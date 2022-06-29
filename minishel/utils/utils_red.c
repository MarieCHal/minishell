/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_red.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchalard <mchalard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 09:29:22 by mchalard          #+#    #+#             */
/*   Updated: 2022/06/28 17:01:20 by mchalard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_search_red(char **cmd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmd[j])
	{
		i = 0;
		while (cmd[j][i])
		{
			if (cmd[j][i] == '<' || cmd[j][i] == '>')
				return (1);
			i++;
		}
		j++;
	}
	return (0);
}

//to copy the lines when parsing redirections
char	*ft_strncpy_red(char *str, int start, int end)
{
	int		i;
	int		j;
	char	*dest;

	dest = malloc(sizeof(char) * (ft_len_red(str, start) + 1));
	j = 0;
	i = start;
	while (i < end)
	{
		dest[j] = str[i];
		j++;
		i++;
	}
	dest[j] = '\0';
	return (dest);
}

int	ft_len_post_red(char **tab)
{
	int	j;
	int	len;

	j = 0;
	len = 0;
	while (tab[j])
	{
		if (tab[j][0] != '<' && tab[j][0] != '>')
			len++;
		j++;
	}
	return (len - 1);
}
