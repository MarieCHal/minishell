/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_heredocs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchalard <mchalard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 16:02:16 by mchalard          #+#    #+#             */
/*   Updated: 2022/06/30 16:08:00 by mchalard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**cpy_tab_heredocs(char **tab, int nb_lines, char *input)
{
	char	**copied_tab;
	int		j;

	j = 0;
	copied_tab = malloc(sizeof(char *) * (nb_lines + 1));
	while (tab[j])
	{
		copied_tab[j] = copy_new_line(tab[j]);
		j++;
	}
	if (input)
	{
		copied_tab[j] = copy_new_line(input);
		copied_tab[j + 1] = 0;
	}
	else
		copied_tab[j] = 0;
	return (copied_tab);
}

int	ft_freed(t_fd *files, char *input)
{
	files->tab_in = malloc(sizeof(char *) * 2);
	files->tab_in[0] = copy_new_line(input);
	files->tab_in[1] = 0;
	return (0);
}

void	ft_not_freed(t_fd *files, char *input, int nb_lines)
{
	char	**tmp;

	tmp = cpy_tab_heredocs(files->tab_in, nb_lines, input);
	free_tab(files->tab_in);
	files->tab_in = cpy_tab_heredocs(tmp, nb_lines, NULL);
	free_tab(tmp);
}

char	*ft_input(void)
{
	char	*input;

	input = readline("> ");
	if (!input)
		return (NULL);
	if (input[0] == '\0')
	{
		free(input);
		input = copy_new_line(" \0");
	}
	return (input);
}

void	check_heredoc(char *key_word, t_fd *files)
{
	char		*input;
	int			nb_lines;
	static int	freed = 1;

	nb_lines = 1;
	if (files->heredocs == 1)
		free_tab(files->tab_in);
	input = ft_input();
	while (1)
	{
		if ((ft_strncmp(input, key_word, ft_strlen(input)) == 0)
			&& (ft_strlen(input) == ft_strlen(key_word)))
			break ;
		if (freed == 1)
			freed = ft_freed(files, input);
		else
			ft_not_freed(files, input, nb_lines);
		free(input);
		input = ft_input();
		nb_lines++;
	}
	if (input)
		free(input);
	freed = 1;
	files->heredocs = 1;
}
