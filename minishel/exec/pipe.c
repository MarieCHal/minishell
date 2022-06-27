/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchalard <mchalard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 11:32:10 by mchalard          #+#    #+#             */
/*   Updated: 2022/06/27 13:57:00 by mchalard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	create_pipe(int nb_pipe, int fd[nb_pipe][2])
{
	int	i;

	i = 0;
	while (i < nb_pipe)
	{
		pipe(fd[i]);
		i++;
	}
}

//closes pipes
void	close_pipes(int nb_pipe, int fd[nb_pipe][2])
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

int	ft_exec_child(char **cmd, int nb_pipe, int fd[nb_pipe][2], int i, t_fd *files, t_tab *tab)
{
	int	j;

	j = 0;
	if (i > 0)
		dup2(fd[i - 1][0], STDIN_FILENO);
	if (i < nb_pipe)
		dup2(fd[i][1], STDOUT_FILENO); 
	close_pipes(nb_pipe, fd);
	if (files->red == 1)
		exec_red(cmd, files, tab);
	else if (files->red == 0)
		ft_execve(cmd, tab);
	return (0);  
}

//does all the parsing (spaces, redirections) + stocks the fds of red if present
//takes as argument one line of the cmd split according to the pipes
//give back that line in the form of a tab ready to be executed by a child
char	**parsed_tab(char *tab, t_fd *files)
{
	char	**parse_space;
	char	**parse_red;
	char	**new;

	ft_init_red(files);
	parse_space = ft_split(tab, ' ');
	if ((files->red = ft_search_red(parse_space)) == 0)
		return(parse_space);
	parse_red = ft_parse_red(parse_space);
	ft_check_fd_in(parse_red, files);
	new = post_red(parse_red);
	free_tab(parse_space);
	return (new);
}

//takes as arguments the command line split according to 
//the pipes and the number of pipe that have to be created
int ft_pipe(char **cmd, int nb_pipe, int i, t_tab *tab)
{
	t_fd	files;
	int		fd[nb_pipe][2];
	char	**cmd_parsed;
	int		pid;
	int		status;

	create_pipe(nb_pipe, fd);
	while (i <= nb_pipe)
	{
		cmd_parsed = parsed_tab(cmd[i], &files);
		pid = fork();
		if (pid == 0)
		{
			ft_exec_child(cmd_parsed, nb_pipe, fd, i, &files, tab);
			close_pipes(nb_pipe, fd);
			exit(0);
		}
		if (files.tab_in)
			free_tab(files.tab_in);
		free_tab(cmd_parsed);
		i++;
	}
	close_pipes(nb_pipe, fd);
	waitpid(pid, &status, 0);
	exit_status = WEXITSTATUS(status);
	return (0);
}
