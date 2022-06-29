/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeauman <gbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 13:37:05 by gbeauman          #+#    #+#             */
/*   Updated: 2022/06/28 17:00:17 by gbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../minishell.h"

void	ft_var_del(t_tab *tab, int j)
{
	char	**stock;
	int		i;
	int		len;

	i = 0;
	stock = NULL;
	stock = envp_cpy(tab, stock);
	len = 0;
	while (stock[len])
		len++;
	free_tab (tab->envp);
	tab->envp = malloc (len * sizeof(tab->envp));
	while (i < j)
	{
		tab->envp[i] = ft_strdup(stock[i]);
		i++;
	}
	j++;
	while (stock[j])
	{
		tab->envp[i] = ft_strdup(stock[j]);
		i++;
		j++;
	}
	tab->envp[i] = NULL;
	free_tab(stock);
}

int	check_var_comp(char *var)
{
	int	i;

	i = 0;
	while (var[i])
		i++;
	if (check_valid_id(var, i) == 1)
		return (1);
	return (0);
}

int	ft_remove_var(t_tab *tab, int j, char *var)
{
	int	i;

	i = 0;
	while (tab->envp[j][i] != '=' && tab->envp[j][i])
		i++;
	if (ft_strncmp(var, tab->envp[j], i) == 0 && ((size_t)i == ft_strlen(var)))
	{
		ft_var_del(tab, j);
		return (0);
	}
	return (1);
}

int	ft_check_remove(t_tab *tab, char *var)
{
	int	j;

	j = 0;
	if (var[0] == '=')
	{
		printf ("prompt> unset: `%s': not a valid identifier\n", var);
		return (1);
	}
	else
	{
		while (tab->envp[j])
		{
			if (check_var_comp(var) == 1)
				return (1);
			else if (ft_remove_var(tab, j, var) == 0)
				return (0);
			j++;
		}
	}
	return (0);
}

int	ft_unset(t_tab *tab, char **var)
{
	int	i;

	i = 1;
	while (var[i])
	{
		if (ft_check_remove(tab, var[i]) == 1)
			return (1);
		i++;
	}
	return (0);
}
