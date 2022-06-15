/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_red.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchalard <mchalard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 13:16:37 by mchalard          #+#    #+#             */
/*   Updated: 2022/06/15 10:55:57 by mchalard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int   ft_len_post_red(char **tab)
{
    int j;
    int len;

    j = 0;
    len = 0;
    while (tab[j])
    {
        if (tab[j][0] != '<' && tab[j][0] != '>')
            len++; 
        j++;
    }
    return (len - 1);
}

char **post_red(char **tab)
{
    int j;
    int j_new;
    char **post_red;

    j = 0;
    j_new = 0;
    post_red = malloc(sizeof(char *) * (ft_len_post_red(tab) + 1));
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
    return(post_red);    
}

char    **ft_parse_red(char **tab)
{
    char    **parse_tab;
    int     nb_red;
    int     nb_words;
    int     i_tab;
    int     j_tab;
    int     j_new;
    
    j_new = 0;
    i_tab = 0;
    j_tab = 0;
    nb_words = count_words_red(tab, '<', '>');
    nb_red = ft_count_red(tab, '<') + ft_count_red(tab, '>');
    parse_tab = malloc(sizeof(char *) * (nb_words + nb_red + 1));
    while (tab[j_tab])
    {
        i_tab = 0;
        while (tab[j_tab][i_tab])
        {
            if (tab[j_tab][i_tab] != '>' && tab[j_tab][i_tab] != '<')
            {
                parse_tab[j_new] = ft_strncpy_red(tab[j_tab], i_tab, i_tab + ft_len_red(tab[j_tab], i_tab));
                i_tab += ft_len_red(tab[j_tab], i_tab);
            }
            else
            {
                if (tab[j_tab][i_tab + 1] == tab[j_tab][i_tab])
                {
                    parse_tab[j_new] = malloc(sizeof(char) * 3);
                    parse_tab[j_new][0] = tab[j_tab][i_tab];
                    parse_tab[j_new][1] = tab[j_tab][i_tab];
                    parse_tab[j_new][2] = '\0';
                    i_tab++;
                }
                else
                {
                    parse_tab[j_new] = malloc(sizeof(char) * 2);
                    parse_tab[j_new][0] = tab[j_tab][i_tab];
                    parse_tab[j_new][1] = '\0';
                }
                i_tab++;
            }
            j_new++;
        }
        j_tab++;
    }
    parse_tab[j_new] = 0;
    return(parse_tab);
}
