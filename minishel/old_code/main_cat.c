/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_cat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchalard <mchalard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 13:54:09 by mchalard          #+#    #+#             */
/*   Updated: 2022/06/20 15:36:59 by mchalard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
    char **cmd;

    cmd = ft_split(" salut cat afkjvn coucou | cat<<stop| cat test<lala| cat|ls\0", '|');
    check_cat(cmd);
    while (1)
        ;
    return (0);
}