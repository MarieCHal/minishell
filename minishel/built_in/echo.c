/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchalard <mchalard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 18:13:06 by mchalard          #+#    #+#             */
/*   Updated: 2022/06/29 11:45:13 by mchalard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int    ft_echo(char **tab)
{
    int j;
    
    j = 1;
    if (!tab[1] || ft_strncmp(tab[1], "-n\0", ft_strlen(tab[0]) != 0))
    {
        while (tab[j])
        {
            printf("%s", tab[j]);
            printf(" ");
            j++;
        }
        printf("\n");
    }
    else
    {
        j = 2;
        while (tab[j])
        {
            printf("%s", tab[j]);
            printf(" ");
            j++;
        }
    }
    return (g_exit_status = 0);
}