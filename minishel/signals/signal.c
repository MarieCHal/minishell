/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_signal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchalard <mchalard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 12:53:03 by mchalard          #+#    #+#             */
/*   Updated: 2022/06/29 09:24:01 by mchalard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_if_child(int new_val)
{
	static int	val;

	val = 0;
	if (new_val >= 0)
		val = new_val;
	return (val);
}

void	signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		if (ft_check_if_child(-1) == 0)
		{
			rl_replace_line("", 0);
			ft_putendl_fd("", 1);
			rl_on_new_line();
			rl_redisplay();
			g_exit_status = 1;
		}
		else
		{
			g_exit_status = 128 + signal;
		}
	}
	else if (signal == SIGQUIT)
	{
		g_exit_status = 128 + signal;
		rl_on_new_line();
		rl_redisplay();
	}
}

void    ft_hide_keystrockes(struct termios *sig)
{
    struct termios attr;

    tcgetattr(STDIN_FILENO, sig);
    tcgetattr(STDIN_FILENO, &attr);
    attr.c_lflag &= ~ECHOCTL; 
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &attr);
}

void init_signals(struct termios *sig)
{
    ft_hide_keystrockes(sig);
    signal(SIGINT, signal_handler);
    signal(SIGQUIT, signal_handler);
}
