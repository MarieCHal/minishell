/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchalard <mchalard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 18:41:17 by mchalard          #+#    #+#             */
/*   Updated: 2022/06/30 15:40:04 by mchalard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env_val(char *env, int i)
{
	int		lenght;
	char	*val;

	lenght = i;
	while (env[i])
		i++;
	val = malloc(sizeof(char) * (i - lenght) + 1);
	i = 0;
	while (env[++lenght])
	{
		val[i] = env[lenght];
		i++;
	}
	val[i] = '\0';
	return (val);
}

char	*get_variable_value(char *variable, t_tab *tab)
{
	char	*value;
	int		j;
	int		i;

	j = 0;
	value = NULL;
	if (ft_strncmp(variable, "?\0", ft_strlen(variable)) == 0)
		value = ft_itoa(g_exit_status);
	else
	{
		while (tab->envp[j])
		{
			i = 0;
			while (tab->envp[j][i] != '=' && tab->envp[j][i])
				i++;
			if (ft_strncmp(variable, tab->envp[j], i) == 0
				&& ((size_t)i == ft_strlen(variable)))
				value = get_env_val(tab->envp[j], i);
			j++;
		}
	}
	return (value);
}

int	check_dollar_lenght(int i, char *line)
{
	int	j;

	j = 0;
	i++;
	while ((line[i] != '\0') && (line[i] != '\'')
		&& (line[i] != '\"') && (line[i] != ' ' && (line[i] != '$')))
	{
		i++;
		j++;
	}
	return (j);
}

//replace the $variable per its value
char	*check_dollar(int i, char *line, t_tab *tab)
{
	char	*value;
	char	*variable;
	int		j;

	j = 0;
	variable = malloc(sizeof(char) * check_dollar_lenght(i, line) + 1);
	i++;
	while ((line[i] != '\0') && (line[i] != '\'')
		&& (line[i] != '\"') && (line[i] != ' ' && (line[i] != '$')))
	{
		variable[j] = line[i];
		j++;
		i++;
	}
	variable[j] = '\0';
	value = get_variable_value(variable, tab);
	free(variable);
	return (value);
}

char	*manage_dollar(t_count *count, char *result, char *line, t_tab *tab)
{
	char	*tmp;

	count->k = 0;
	tmp = check_dollar(count->i, line, tab);
	if (tmp != NULL)
	{
		while (tmp[count->k] != '\0')
		{
			result[count->j] = tmp[count->k];
			count->j++;
			count->k++;
		}
		free(tmp);
	}
	count->i += check_dollar_lenght(count->i, line);
	count->i++;
	return (result);
}
