/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchalard <mchalard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 17:01:42 by mchalard          #+#    #+#             */
/*   Updated: 2022/05/20 18:46:06 by mchalard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
    char *input;
    char *result;
    
    input = "coucou \"$HOME\"\'salut ca v$HOME\'";
    result = check_quotes(input);
    printf("input:  %s\n", input);
    printf("output: %s\n", result);
    free(result);
    while (1)
        ;
    return (0);
}