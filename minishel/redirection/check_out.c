/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_out.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchalard <mchalard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 16:01:06 by mchalard          #+#    #+#             */
/*   Updated: 2022/06/15 14:57:38 by mchalard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int check_file_out(char *file_name, t_fd *files, int append)
{
    if (files->fd_out != 0)
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
        return(0);
    }
    return(1);
}