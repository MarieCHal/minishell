/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdin_out.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchalard <mchalard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 13:36:22 by mchalard          #+#    #+#             */
/*   Updated: 2022/06/26 16:26:40 by mchalard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_file_in(char *file_name, t_fd *files)
{
	if (files->fd_in != -1)
		close(files->fd_in);
	files->fd_in = open(file_name, O_RDONLY);
	if (files->fd_in == -1)
	{
		printf("bash: %s: no such file or directory\n", file_name);
		return (0);
	}
	if (files->heredocs == 1)
	{
		free_tab(files->tab_in);
		files->heredocs = 0;
	}
	return (1);
}

int	check_file_out(char *file_name, t_fd *files, int append)
{
	if (files->fd_out != -1)
		close(files->fd_out);
	if (append == 1)
		files->fd_out = open(file_name, O_WRONLY | O_APPEND | O_CREAT, 0666);
	if (append == 0)
		files->fd_out = open(file_name, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	if (files->fd_out == -1)
	{
		if (!file_name)
			printf("bash: syntax error near unexpected token `newline'\n");
		else
			printf("error while creating file %s\n", file_name);
		return (0);
	}
	return (1);
}

int	ft_check_fd_in(char **tab, t_fd *files)
{
	int	j;

	j = 0;
	while (tab[j])
	{
		if (tab[j][0] == '<' && tab[j][1] != '<')
		{
			if (!(check_file_in(tab[j + 1], files)))
				return (0);
		}
		if (tab[j][0] == '<' && tab[j][1] == '<')
			check_heredoc(tab[j + 1], files);
		if (tab[j][0] == '>' && tab[j][1] != '>')
		{
			if (!(check_file_out(tab[j + 1], files, 0)))
				return (0);
		}
		if (tab[j][0] == '>' && tab[j][1] == '>')
		{
			if (!(check_file_out(tab[j + 1], files, 1)))
				return (0);
		}
		j++;
	}
	return (1);
}
