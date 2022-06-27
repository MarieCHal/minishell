/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_single.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchalard <mchalard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 10:56:19 by mchalard          #+#    #+#             */
/*   Updated: 2022/06/27 15:09:47 by mchalard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_exec_single_cmd(char **cmd, char **result, t_fd *files, t_tab *tab)
{
	char	**cmd_args;

	cmd_args = replace_quotes(cmd, tab);
	if (files->red == 1)
		exec_red(cmd, files, tab);
	else if (files->red == 0)
	{
		if (check_our_built_in(cmd_args, tab) == 1)
			check_cmd(result, tab);
	}
	free_tab(cmd_args);
	return (0);
}

int	ft_count_cmd(char **result, t_tab *tab)
{
	int		j;
	t_fd	files;
	char	**new;

	j = 0;
	new = NULL;
	while (result[j])
		j++;
	if (j > 1 || ft_strlen(result[0]) == 0)
		return (0);
	else
		new = parsed_tab(result[0], &files);
	ft_exec_single_cmd(new, result, &files, tab);
	free_tab(new);
	free_tab(result);
	return (1);
}
