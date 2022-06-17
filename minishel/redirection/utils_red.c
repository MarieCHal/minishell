/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_red.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchalard <mchalard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 09:29:22 by mchalard          #+#    #+#             */
/*   Updated: 2022/06/17 14:32:57 by mchalard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//check error in number of red
int error_red(char *cmd, t_fd *files)
{
    int i;
    
    i = 0;
    while (cmd[i])
    {
        if (cmd[i] == '<' || cmd[i] == '>')
        {
            files->red = 1;
            /*if (cmd[i + 1] == cmd[i] && cmd[i + 2] == cmd[i])
            {
                printf("syntax error near unexpected token `%c'\n", cmd[i + 2]);
                return (0);
            }
            if ((cmd[i] == '<' && cmd[i + 1] == '>') || (cmd[i] == '>' && cmd[i + 1] == '<'))
            {
                
            }*/
        }
        i++;
    }
    return (1);
}

//to copy the lines when parsing redirections
char	*ft_strncpy_red(char *str, int start, int end)
{
	int	i;
	int	j;
	char *dest;

	dest = malloc(sizeof(char) * (ft_len_red(str, start) + 1));
	j = 0;
	i = start;
	while (i < end)
	{
		dest[j] = str[i];
		j++;
		i++;
	}
	dest[j] = '\0';
	return(dest);
}

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

void    close_fd(t_fd *files)
{
    if (files->heredocs == 1)
        free_tab(files->tab_in);
    if (files->fd_in != -1)
        close(files->fd_in);
    if (files->fd_out != -1)
        close(files->fd_out); 
}

//initialize the struct for redirections
//-------->replace the initialization of fd in and out at -1
void    ft_init_red(t_fd *files)
{
    files->append = 0;
    files->fd_in = -1;
    files->fd_out = -1;
    files->heredocs = 0;
    files->red = 0;
}

