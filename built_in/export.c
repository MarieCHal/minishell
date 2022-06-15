/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeauman <gbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 12:45:53 by gbeauman          #+#    #+#             */
/*   Updated: 2022/06/15 15:20:29 by gbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../minishell.h"

void	free_envp(t_tab *tab);

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
	tab->envp = malloc (i *sizeof (tab->envp));
	while (i2 < i - 2)
	{
		tab->envp[i2] = ft_strdup(envp_stock[i2]);
		i2++;
	}
	tab->envp[i2] = ft_strdup(var);
	tab->envp[i2 + 1] = NULL;
}

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

int		check_equal(char *var)
{
	int	i;
	
	i = 0;
	while (var[i])
	{
		if (var[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

/*void	ft_order(t_tab *tab)
{
	char	**order;
	int	j;

	j = 0;
	
}*/

void	ft_var_new_value(t_tab *tab, char *var, int j)
{
	int	len;
	int	i;

	i = 0;
	len = ft_strlen(var);
	tab->envp[j] = malloc(len + 1 *sizeof(char));
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
		printf ("waiting\n");
		//ft_order(tab);
	while (var[i])
	{
		if (!check_equal(var[i]))
			var[i] = NULL;
		else if (ft_check_exist_var(tab, var[i]))
			var[i] = NULL;
		envp_stock = envp_cpy(tab, envp_stock);
		new_envp(tab, envp_stock, var[i]);
		free (envp_stock);
		i++;
	}
}
