/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchalard <mchalard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 16:02:16 by mchalard          #+#    #+#             */
/*   Updated: 2022/06/17 14:46:38 by mchalard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int check_file_in(char *file_name, t_fd *files)
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


char **cpy_tab_heredocs(char **tab, int nb_lines, char *input)
{
    char **copied_tab;
    int j;

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
    return(copied_tab);
}

void    check_heredoc(char *key_word, t_fd *files)
{
    char *input;
    int nb_lines;
    char    **tmp;
    static int  freed = 1;
    
    nb_lines = 1;
    if (files->heredocs == 1)
        free_tab(files->tab_in);
    input = readline("> ");
    while ((ft_strncmp(input, key_word, ft_strlen(key_word)) != 0))
    {
        if (freed == 1)
        {
            files->tab_in = malloc(sizeof(char *) * 2);
            files->tab_in[0] = copy_new_line(input);
            files->tab_in[1] = 0;
            freed = 0;
        }
        else
        {
            tmp = cpy_tab_heredocs(files->tab_in, nb_lines, input);
            free_tab(files->tab_in);
            files->tab_in = cpy_tab_heredocs(tmp, nb_lines, NULL);
            free_tab(tmp);
        }
        free(input);
        input = readline("> ");
        nb_lines++;
    }
    freed = 1;
    files->heredocs = 1;
}