/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_close.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchalard <mchalard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 16:41:41 by mchalard          #+#    #+#             */
/*   Updated: 2022/06/29 11:39:57 by mchalard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_wait_pid(t_fd *files)
{
	int		status;
	int	i;

	i = 0;
	while (i <= files->nb_pipe)
	{
		ft_check_if_child(files->pid[i]);
		waitpid(files->pid[i], &status, 0);
		if (WIFEXITED(status))
			g_exit_status = WEXITSTATUS(status);
		i++;
	}
	ft_check_if_child(0);
	return (0);
}

void	free_tab(char **tab_to_free)
{
	int	j;

	j = 0;
	if (tab_to_free != NULL)
	{
		while (tab_to_free[j])
		{
			free(tab_to_free[j]);
			j++;
		}
		free(tab_to_free);
	}
}

void	free_double(char *stock, char *tmp)
{
	if (stock != 0)
        free(stock);
    if (tmp != 0)
        free(tmp);
}

void	close_pipes(int nb_pipe, int (*fd)[2])
{
	int	j;

	j = 0;
	while (j < nb_pipe)
	{
		close(fd[j][0]);
		close(fd[j][1]);
		j++;
	}
}

void	close_fd(t_fd *files)
{
	if (files->heredocs == 1 && files->tab_in != NULL)
		free_tab(files->tab_in);
	if (files->fd_in != -1)
		close(files->fd_in);
	if (files->fd_out != -1)
		close(files->fd_out); 
}