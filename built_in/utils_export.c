/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeauman <gbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 18:28:00 by gbeauman          #+#    #+#             */
/*   Updated: 2022/06/21 18:31:35 by gbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../minishell.h"

void	free_envp(t_tab *tab)
{
	int	i;

	i = 0;
	while (tab->envp[i])
	{
		free (tab->envp[i]);
		i++;
	}
}

char	**envp_cpy(t_tab *tab, char **envp_stock)
{
	int	i;
	int	i2;

	i = 0;
	i2 = 0;
	while (tab->envp[i])
		i++;
	i += 1;
	envp_stock = malloc (i * sizeof(envp_stock));
	while (i2 < i - 1)
	{
		envp_stock[i2] = ft_strdup(tab->envp[i2]);
		i2++;
	}
	envp_stock[i2] = NULL;
	free_envp (tab);
	return (envp_stock);
}

void	new_envp(t_tab *tab, char **envp_stock, char *var)
{
	int	i;
	int	i2;

	i = 0;
	i2 = 0;
	while (envp_stock[i])
		i++;
	i += 2;
	tab->envp = malloc (i * sizeof (tab->envp));
	while (i2 < i - 2)
	{
		tab->envp[i2] = ft_strdup(envp_stock[i2]);
		i2++;
	}
	tab->envp[i2] = ft_strdup(var);
	tab->envp[i2 + 1] = NULL;
}

int	check_valid_id(char *var, int end)
{
	int	i;

	i = 0;
	while (i < end)
	{
		if (var[i] == 95)
			i++;
		else if ((var[i] < 65 || var[i] > 90) && (var[i] < 97 || var[i] > 122))
		{
			printf ("prompt> export: `%s': not a valid identifier\n", var);
			return (0);
		}
		i++;
	}
	return (1);
}

int	check_equal(char *var)
{
	int	i;

	i = 0;
	while (var[i])
	{
		if (var[0] == '=')
		{
			printf ("prompt> export: `%s': not a valid identifier\n", var);
			return (0);
		}
		else if (var[i] == '=')
		{
			if (check_valid_id(var, i) == 0)
				return (0);
			else
				return (1);
		}
		i++;
	}
	return (0);
}
