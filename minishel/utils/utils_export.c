/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchalard <mchalard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 14:28:44 by mchalard          #+#    #+#             */
/*   Updated: 2022/06/30 15:09:23 by mchalard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../minishell.h"

void	fill_new_envp(t_tab *tab, char **envp_stock, char *var)
{
	envp_stock = envp_cpy(tab, envp_stock);
	new_envp(tab, envp_stock, var);
	free_tab (envp_stock);
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
	free_tab (tab->envp);
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
			return (1);
		}
		i++;
	}
	return (0);
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
			return (1);
		}
		else if (var[i] == '=')
		{
			if (check_valid_id(var, i))
				return (1);
		}
		i++;
	}
	return (0);
}
