/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchalard <mchalard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 10:45:20 by mchalard          #+#    #+#             */
/*   Updated: 2022/06/16 12:10:10 by mchalard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//returns a tab with all the $replaced and the quotes managed
char    **replace_quotes(char **tab)
{
    int j;
    char    **new_tab;
    
    j = 0;
    while (tab[j])
        j++;
    new_tab = malloc(sizeof(char *) * (j + 1));
    j = 0;
    while (tab[j])
    {
        new_tab[j] = check_quotes(tab[j]);
        j++;
    }
    new_tab[j] = 0;
    return(new_tab);
}
