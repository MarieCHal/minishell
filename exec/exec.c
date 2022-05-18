/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchalard <mchalard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 11:52:59 by mchalard          #+#    #+#             */
/*   Updated: 2022/05/17 18:35:12 by mchalard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int built_in(char *command)
{
    DIR *dir;
    const char *args;
    const char    *com;
    struct dirent *dent;
    int             i;
    
    i = 0;
    args = "built_in";
    dir = opendir(args);
    if (dir == NULL)
        printf("error\n");
    while ((dent = readdir(dir)) != NULL)
    {
        com = dent->d_name;
        if (ft_strncmp(command, com, ft_strlen(command)) == 0)
            return (i);
        i++;
    }
    return (0);
}
