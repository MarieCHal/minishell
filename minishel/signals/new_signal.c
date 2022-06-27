/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_signal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchalard <mchalard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 12:53:03 by mchalard          #+#    #+#             */
/*   Updated: 2022/06/20 12:57:25 by mchalard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void signal_handler(int signal)
{
    if (signal == SIGINT)
    {
        //g_sig = 128 + SIGINT;
        rl_replace_line("", 0);
        ft_putendl_fd("",1);
        rl_on_new_line();
        rl_redisplay();
    }
    else if (signal == SIGQUIT)
    {
        //g_sig = 128 + SIGQUIT;
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
