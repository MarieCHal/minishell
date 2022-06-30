/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_red.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchalard <mchalard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 13:16:37 by mchalard          #+#    #+#             */
/*   Updated: 2022/06/30 14:02:00 by mchalard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**post_red(char **tab)
{
	int		j;
	int		j_new;
	char	**post_red;

	j = 0;
	j_new = 0;
	post_red = malloc(sizeof(char *) * (ft_len_post_red(tab) + 2));
	while (tab[j])
	{
		if (tab[j][0] == '<' || tab[j][0] == '>')
			j = j + 1;
		else
		{
			post_red[j_new] = copy_new_line(tab[j]);
			j_new++;
		}
		j++;
	}
	post_red[j_new] = 0;
	free_tab(tab);
	return (post_red);
}

//function to copy the redirections (<, <<, >>, >)
char	*ft_copy_red(char char1, char char2, int i, char *tab)
{
	char	*red;

	if (char1 == char2)
		red = ft_strncpy(tab, i, i + 2);
	else
		red = ft_strncpy(tab, i, i + 1);
	return (red);
}

void	ft_init_struct_red(t_red *red, char **tab)
{
	red->n = 0;
	red->j = 0;
	red->new = malloc(sizeof(char *) * (count_words_red(tab, '<', '>')
				+ ft_count_red(tab, '<') + ft_count_red(tab, '>') + 1));
}

void	ft_set_new(t_red *red, char **tab)
{
	if (tab[red->j][red->i] != '>' && tab[red->j][red->i] != '<')
	{
		red->new[red->n] = ft_strncpy_red(tab[red->j],
				red->i, red->i + ft_len_red(tab[red->j], red->i));
		red->i += ft_len_red(tab[red->j], red->i);
	}
	else
	{
		red->new[red->n] = ft_copy_red(tab[red->j][red->i],
				tab[red->j][red->i + 1], red->i, tab[red->j]);
		if (ft_strlen(red->new[red->n]) == 2)
			red->i++;
		red->i++;
	}
}

char	**ft_parse_red(char **tab)
{
	t_red	red;

	ft_init_struct_red(&red, tab);
	while (tab[red.j])
	{
		red.i = 0;
		while (tab[red.j][red.i])
		{
			ft_set_new(&red, tab);
			red.n++;
		}
		red.j++;
	}
	red.new[red.n] = 0;
	return (red.new);
}
