/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchalard <mchalard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 15:28:40 by mchalard          #+#    #+#             */
/*   Updated: 2022/06/02 18:03:31 by mchalard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sig_int(int sig)
{
	if (sig == SIGINT)
	{
		//printf(" \n");
		kill(pid_kill, SIGKILL);
	}
	//printf("\n");
}

/*void    sig_segv()
{
    exit(0);
}*/