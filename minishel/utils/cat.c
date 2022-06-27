/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchalard <mchalard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 14:03:31 by mchalard          #+#    #+#             */
/*   Updated: 2022/06/26 16:51:15 by mchalard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// checks if there is a file as input for cat
int	check_cat_input(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i][0] == '<')
			return (1);
		i++;
	}
	return (0);
}

void	ft_print_cat(int nb_cat)
{
	char	*rd;

	while (nb_cat != 0)
	{
		rd = readline("");
		nb_cat--;
		free(rd);
	}
}

int	ft_search_cat_red(char **cmd)
{
	char	**tmp;
	int		trigger;
	int		i;

	i = 0;
	trigger = 0;
	tmp = ft_parse_red(cmd);
	while (tmp[i])
	{
		if (ft_strncmp(tmp[i], "cat\0", ft_strlen(tmp[i])) == 0)
		{
			trigger = check_cat_input(tmp);
			free_tab(tmp);
			return (trigger);
		}
		i++;
	}
	free_tab(tmp);
	return (1);
}

//goes through the cmd to check if there is a cat and if it has an input
//sends the cmd to ft_search_cat_red if there is a red to be sure that they are all taken in consideration
int	ft_search_cat(char **cmd)
{
	int	i;
	int	trigger;

	i = 0;
	trigger = 0;
	if (ft_search_red(cmd) == 1)
	{
		trigger = ft_search_cat_red(cmd);
		return (trigger);
	}
	else 
	{
		while (cmd[i])
		{
			if (ft_strncmp(cmd[i], "cat\0", ft_strlen(cmd[i])) == 0)
			{
				trigger = check_cat_input(cmd);
				return (trigger);
			}
			i++;
		}
	}
	return (1);
}

int	ft_trigger(char **cmd)
{
	int	trigger;

	trigger = 0;
	trigger = ft_search_cat(cmd);
	if (trigger == 0)
		return (0);
	else
		return (1);
}

int	check_cat(char **result)
{
	int		nb_cat;
	int		i;
	int		j;
	char	**cmd;

	j = 0;
	nb_cat = 0;
	if (!result[0])
		return (0);
	if (ft_strncmp(result[0], "cat\0", 3) != 0)
		return (0);
	while (result[j])
	{
		i = 0;
		cmd = ft_split(result[j], ' ');
		if (ft_trigger(cmd) == 1)
			break ;
		nb_cat++;
		free_tab(cmd);
		cmd = NULL;
		j++;
	}
	ft_print_cat(nb_cat);
	free_tab(cmd);
	return (0);
}
