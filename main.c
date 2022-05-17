/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchalard <mchalard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 13:45:19 by mchalard          #+#    #+#             */
/*   Updated: 2022/05/12 16:28:34 by mchalard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
    char *cmd;
    char    **result;
    int     j;
    
    while (1)
    {
        result = NULL;
        j = 0;
        cmd = readline("prompt>");
        add_history(cmd);
        result = ft_split(cmd, ' ');
        while (result[j])
        {
            printf("%s ", result[j]);
            printf("j: %d\n", j);
            j++;
        }
    }
}