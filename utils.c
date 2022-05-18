/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchalard <mchalard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 15:56:12 by mchalard          #+#    #+#             */
/*   Updated: 2022/05/17 16:21:07 by mchalard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*char	*ft_strjoin(char *s1, char *s2)
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
}*/