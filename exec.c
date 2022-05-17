/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchalard <mchalard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 11:52:59 by mchalard          #+#    #+#             */
/*   Updated: 2022/05/13 13:01:37 by mchalard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int main(void)
{
    char *envp[] = {NULL};
    char    *argv[] = {"cat", "/Users/mchalard/Desktop/rank 03/minishel/main.c", NULL};
    
    execve("/bin/cat", argv, envp);
    return (0);
}