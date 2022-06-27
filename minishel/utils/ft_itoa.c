/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchalard <mchalard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 14:23:30 by mchalard          #+#    #+#             */
/*   Updated: 2022/06/26 16:54:51 by mchalard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_tableau(unsigned int n, char *c, int len)
{
	while (n > 0)
	{
		c[len] = 48 + (n % 10);
		n = n / 10;
		len--;
	}
	return (c);
}

int	ft_len(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len = 1;
	while (n != 0)
	{
		len++;
		n = n / 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char			*c;
	int				len;
	unsigned int	number;
	char			sign;

	len = ft_len(n);
	c = (char *)malloc(len * sizeof(char) + 1);
	if (!c)
		return (NULL);
	if (n == 0)
	{
		c[0] = 48;
	}
	c[len--] = '\0';
	if (n < 0)
	{
		sign = -1;
		number = n * -1;
		c[0] = '-';
	}
	else
		number = n;
	c = ft_tableau(number, c, len);
	return (c);
}
