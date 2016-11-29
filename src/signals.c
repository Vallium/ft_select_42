/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 11:13:05 by aalliot           #+#    #+#             */
/*   Updated: 2016/11/29 13:13:13 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"
#include <signal.h>

void	sig_win_resize(int i)
{
	(void)i;
	winsize();
	refresh_screen();
}

void	ft_sig_int(int i)
{
	(void)i;
	ft_reset_term();
	exit(0);
}

void	ft_sig_stop(int i)
{
	(void)i;
	ft_reset_term();
}

void	ft_sig_cont(int i)
{
	t_term	*term;

	(void)i;
	term = ft_singleton();
	tcsetattr(0, TCSADRAIN, &(term->termios));
	winsize();
	refresh_screen();
}

void	init_signals()
{
	signal(SIGINT, ft_sig_int);
	signal(SIGQUIT, ft_sig_int);
	signal(SIGWINCH, sig_win_resize);
	signal(SIGSTOP, ft_sig_stop);
	signal(SIGCONT, ft_sig_cont);
}
