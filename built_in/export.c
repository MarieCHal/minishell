/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeauman <gbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 12:45:53 by gbeauman          #+#    #+#             */
/*   Updated: 2022/06/21 18:33:53 by gbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../minishell.h"

void	ft_print_order(char **order, int len)
{
	int	j;

	j = 0;
	while (j < len)
	{
		printf ("declare -x %s\n", order[j]);
		j++;
	}
}

void	ft_order(t_tab *tab)
{
	char	**order;
	int		i;
	int		j;
	int		j_order;
	int		len;

	j_order = 0;
	i = 0;
	len = 0;
	while (tab->envp[len])
		len++;
	order = malloc (len * sizeof(order));
	while (i++ <= 122)
	{
		j = 0;
		while (j < len)
		{
			if (tab->envp[j][0] == i)
				order[j_order++] = ft_strdup(tab->envp[j]);
			j++;
		}
	}
	ft_print_order(order, len);
}

void	ft_var_new_value(t_tab *tab, char *var, int j)
{
	int	len;
	int	i;

	i = 0;
	len = ft_strlen(var);
	tab->envp[j] = malloc(len + 1 * sizeof(char));
	while (var[i])
	{
		tab->envp[j][i] = var[i];
		i++;
	}
	tab->envp[j][i] = '\0';
}

int	ft_check_exist_var(t_tab *tab, char *var)
{
	int	j;
	int	len;

	j = 0;
	len = 0;
	while (var[len] != '=')
		len++;
	while (tab->envp[j])
	{
		if (ft_strncmp(tab->envp[j], var, len) == 0)
		{
			ft_var_new_value(tab, var, j);
			return (1);
		}
		j++;
	}
	return (0);
}

void	ft_export(t_tab *tab, char **var)
{
	char	**envp_stock;
	int		i;

	i = 1;
	envp_stock = NULL;
	if (var[i] == NULL)
		ft_order(tab);
	while (var[i])
	{
		if (!check_equal(var[i]))
			var[i] = NULL;
		else if (ft_check_exist_var(tab, var[i]))
			var[i] = NULL;
		else
		{
			envp_stock = envp_cpy(tab, envp_stock);
			new_envp(tab, envp_stock, var[i]);
			free (envp_stock);
		}
		i++;
	}
}
