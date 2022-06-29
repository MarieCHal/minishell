/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchalard <mchalard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 14:28:06 by mchalard          #+#    #+#             */
/*   Updated: 2022/06/29 16:54:26 by mchalard         ###   ########.fr       */
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
	int		len;

	i = 0;
	len = 0;
	while (tab->envp[len])
		len++;
	len ++;
	order = malloc (len* sizeof(order));
	while (i++ <= 122)
	{
		j = 0;
		while (tab->envp[j])
		{
			if (tab->envp[j][0] == i)
				order[j] = ft_strdup(tab->envp[j]);
			j++;
		}
	}
	printf ("%d\n", j);
	order[j] = NULL;
	ft_print_order(order, len - 1);
	free_tab(order);
}

void	ft_var_new_value(t_tab *tab, char *var, int j)
{
	int	len;
	int	i;

	i = 0;
	len = ft_strlen(var);
	free(tab->envp[j]);
	tab->envp[j] = malloc(len + 1 * sizeof(char));
	while (var[i])
	{
		tab->envp[j][i] = var[i];
		i++;
	}
	tab->envp[j][i] = '\0';
	free (var);
}

int	ft_check_exist_var(t_tab *tab, char *var)
{
	int	j;
	int	len;

	j = 0;
	len = 0;
	while (var[len] != '=' && var[len])
		len++;
	while (tab->envp[j])
	{
		if (ft_strncmp(tab->envp[j], var, len) == 0)
		{
			ft_var_new_value(tab, var, j);
			return (0);
		}
		j++;
	}
	return (1);
}

int	ft_export(t_tab *tab, char **var)
{
	char	**envp_stock;
	int		i;

	i = 1;
	envp_stock = NULL;
	if (var[i] == NULL)
	{
		ft_order(tab);
		return (0);
	}
	while (var[i])
	{
		if (check_equal(var[i]) == 1)
			return (1);
		else if (ft_check_exist_var(tab, var[i]) == 0)
			var[i] = NULL;
		else
			fill_new_envp(tab, envp_stock, var[i]);
		i++;
	}
	return (0);
}
