/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_part_two.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchalard <mchalard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 16:22:36 by mchalard          #+#    #+#             */
/*   Updated: 2022/06/28 16:59:25 by mchalard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
}

void	ft_putendl_fd(char *s, int fd)
{
	char	c;

	c = '\n';
	ft_putstr_fd(s, fd);
	write(fd, &c, 1);
}

char	*ft_strdup(const char *s1)
{
	char	*str;
	int		i;

	i = 0;
	if (!s1)
		return (NULL);
	while (s1[i])
		i++;
	str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
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
