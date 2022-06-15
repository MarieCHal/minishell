/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdin_out.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchalard <mchalard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 13:36:22 by mchalard          #+#    #+#             */
/*   Updated: 2022/06/15 11:04:00 by mchalard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//function to close files;
/*void    ft_close_file(int fd)
{
    
}*/


int ft_check_fd_in(char **tab, t_fd *files)
{
    int j;

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
                return(0);
        } 
        j++;
    }
    j = 0;
    if (files->heredocs == 1)
    {
        while (files->tab_in[j])
        {
            printf("you wrote: %s\n", files->tab_in[j]);
            j++;
        }
    }
    printf("files->heredocs = %d\n", files->heredocs);
    return (1);
}