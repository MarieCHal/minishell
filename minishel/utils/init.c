/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchalard <mchalard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 16:36:19 by mchalard          #+#    #+#             */
/*   Updated: 2022/06/29 09:09:59 by mchalard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	envp_init(t_tab *tab, char **envp)
{
	int	i;
	int	i2;

	i = 0;
	i2 = 0;
	while (envp[i])
		i++;
	i++;
	tab->envp = malloc (i * sizeof(tab->envp));
	while (i2 < i - 1)
	{
		tab->envp[i2] = ft_strdup(envp[i2]);
		i2++;
	}
	tab->envp[i2] = NULL;
}

//initialize the struct for redirections
//-------->replace the initialization of fd in and out at -1
void	ft_init_red(t_fd *files)
{
	files->append = 0;
	files->fd_in = -1;
	files->fd_out = -1;
	files->heredocs = 0;
	files->red = 0;
	files->error = 0;
	files->tab_in = NULL;
}

void	ft_init_built_in(t_tab *tab)
{
	tab->dir = NULL;
	tab->pwd_var = "PWD=";
	tab->oldpwd_var = "OLDPWD=";
	tab->home_path = "/Users/mchalard";
	tab->envp = NULL;
}
