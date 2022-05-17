/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeauman <gbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 11:59:44 by gbeauman          #+#    #+#             */
/*   Updated: 2022/05/17 13:45:34 by gbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

int	main(void)
{
	char	*cmd;
	char	**result;
	char	**tab1;
	int		i;
	int		j;

	while (1)
	{
		result = NULL;
		tab1 = NULL;
        j = 0;
		i = 0;
        cmd = readline("prompt> ");
        add_history(cmd);
        result = ft_split_pipe(cmd, '|');
        while (result[j])
        {
			printf ("pipe :%s\n", result[j]);
			tab1 = ft_split(result[j], ' ');
			while (tab1[i])
			{
				printf ("test :%s\n", tab1[i]);
				i++;
			}
			free(tab1);
			i = 0;
            j++;
        }
    }
}