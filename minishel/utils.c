/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchalard <mchalard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 15:56:12 by mchalard          #+#    #+#             */
/*   Updated: 2022/06/16 09:30:44 by mchalard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//copies str from start to end 
char	*ft_strncpy(char *str, int start, int end)
{
	int	i;
	int	j;
	char *dest;

	dest = malloc(sizeof(char) * (end - start + 1));
	j = 0;
	i = start;
	while (i < end)
	{
		dest[j] = str[i];
		j++;
		i++;
	}
	dest[j] = '\0';
	return(dest);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			i;

	str1 = (unsigned char *) s1;
	str2 = (unsigned char *) s2;
	i = 0;
	while (i < n && str1[i] == str2[i] && str1[i] && str2[i])
		i++;
	if (i == n)
		return (0);
	return ((unsigned char) str1[i] - str2[i]);
}

char	*ft_strjoin_line(char *s1, char *s2)
{
	int		i1;
	int		i2;
	char	*s3;

	i1 = 0;
	i2 = 0;
	if (!s2)
		return (NULL);
	s3 = malloc((ft_strlen(s1) +ft_strlen(s2)) * sizeof(char) + 1);
	if (!s3)
		return (NULL);
	if (s1)
	{
		while (s1[i1])
		{
			s3[i1] = s1[i1];
			i1++;
		}
	}
	while (s2[i2])
	{
		s3[i1] = s2[i2];
		i1++;
		i2++;
	}
	s3[i1] = 0;
	return (s3);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i1;
	int		i2;
	char	*s3;

	i1 = 0;
	i2 = 0;
	if (!s1 || !s2)
		return (NULL);
	s3 = malloc((ft_strlen(s1) +ft_strlen(s2)) * sizeof(char) + 1);
	if (!s3)
		return (NULL);
	while (s1[i1])
	{
		s3[i1] = s1[i1];
		i1++;
	}
	while (s2[i2])
	{
		s3[i1] = s2[i2];
		i1++;
		i2++;
	}
	s3[i1] = 0;
	return (s3);
}

//modified to run with parsing!!!
size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return(0);
	while (s[i] != 0)
		i++;
	return (i);
}

void	free_tab(char **tab_to_free)
{
	int	j;

	j = 0;
	while (tab_to_free[j])
	{
		free(tab_to_free[j]);
		j++;
	}
	free(tab_to_free);
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

char	*mymalloc(const char *s, size_t len)
{
	char	*cpy;

	if (len < ft_strlen(s))
		cpy = malloc(len * sizeof(char) + 1);
	else
		cpy = malloc(ft_strlen(s) * sizeof(char) + 1);
	return (cpy);
}
