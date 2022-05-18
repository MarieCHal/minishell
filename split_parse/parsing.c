/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchalard <mchalard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 14:48:00 by mchalard          #+#    #+#             */
/*   Updated: 2022/05/17 13:08:21 by mchalard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_quotes(const char *str, int i, char q)
{
    i++;
    while (str[i] != q && str[i])
        i++;
    if (str[i] == '\0')
    {
        printf("ok\n");
        return(0);
    }
    return (i);
}

int ft_count_quotes(const char *str, int i, char q)
{
    i++;
    while (str[i] != q)
        i++;
    return(i);
}