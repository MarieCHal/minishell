/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeauman <gbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 13:59:42 by gbeauman          #+#    #+#             */
/*   Updated: 2022/05/12 13:34:36 by gbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define BUFFER_SIZE 100

void	ft_pwd(char *cmd)
{
	char	buffer[BUFFER_SIZE];
	int		i;
	
	i = 0;
	while (cmd[i])
		i++;
	if (i == 3)
	{
		getcwd(buffer, BUFFER_SIZE);
		printf ("%s\n", buffer);
		return;
	}
	i = 4;
	if (cmd[3] != 32)
	{
		print_cmd_not_found(cmd);
		return;
	}
	while (cmd[i])
	{
		if (cmd[i] != 32)
		{
			printf ("pwd: too many arguments\n");
			return;
		}
		i++;
	}
	getcwd(buffer, BUFFER_SIZE);
	printf ("%s\n", buffer);
}