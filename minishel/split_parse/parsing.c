/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchalard <mchalard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 14:48:00 by mchalard          #+#    #+#             */
/*   Updated: 2022/06/14 13:10:45 by mchalard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_quotes(const char *str, int i, char q)
{
    i++;
    while (str[i] != q && str[i])
        i++;
    if (str[i] == '\0')
    {
        printf("error quotes\n");
        return(0);
    }
    return (i);
}

int ft_count_quotes(const char *str, int i, char q)
{
    i++;
    while (str[i] != q)
        i++;
    return(i);
}

int ft_count_red(char **str, char q)
{
    int i;
    int j;
    int nb_red;

    i = 0;
    j = 0;
    nb_red = 0;
    while (str[j])
    {
        i = 0;
        while (str[j][i])
        {
            if (str[j][i] == '\'' || str[j][i] == '\"')
                i = ft_count_quotes(str[j], i, str[j][i]);
            if (str[j][i] == q)
            {
                if (str[j][i + 1] == q)
                    i++;
                nb_red++;
            }
            i++;
        }
        j++;
    }
    return(nb_red);
}

int	count_words_red(char **str, char c1, char c2)
{
	int	word;
    int i;
    int j;

	i = 0;
    j = 0;
    word = 0;
    while (str[j])
    {
        i = 0;
	    while (str[j][i])
	    {
            if (str[j][i] == '\'' || str[j][i] == '\"')
            {
                if ((i = ft_quotes(str[j], i, str[j][i])) == 0)
                    return (0);
            }
		    if (str[j][i] == c1 || str[j][i] == c2)
		    {
                if (str[j][i] == str[j][i + 1])
                    i++;
			    word++;
		    }
		    i++;
	    }
        word++;
        j++;
    }
	return (word);
}

int ft_len_red(char *str, int start)
{
    int i;
    int len;

    i = start;
    len = 0;
    while (str[i])
    {
        if (str[i] == '\'' || str[i] == '\"')
        {
            len += ft_quotes(str, i, str[i]) - 1;
            i += ft_quotes(str, i, str[i]) - 1;
        }
        if (str[i] == '<' || str[i] == '>')
            return (len);
        len++;
        i++;
    }
    return(len);
}