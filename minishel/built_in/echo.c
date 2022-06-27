/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchalard <mchalard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 18:13:06 by mchalard          #+#    #+#             */
/*   Updated: 2022/06/23 11:19:02 by mchalard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int    ft_echo(char **tab)
{
    int j;
    
    j = 1;
    while (tab[j])
    {
        printf("%s", tab[j]);
        printf(" ");
        j++;
    }
    printf("\n");
    return (exit_status = 0);
}