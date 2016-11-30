/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 11:13:05 by aalliot           #+#    #+#             */
/*   Updated: 2016/11/30 16:42:19 by aalliot          ###   ########.fr       */
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
	t_term		*term;
	char		cp[2];

	(void)i;
	if (isatty(1))
	{
		term = ft_singleton();
		cp[0] = term->termios.c_cc[VSUSP];
		cp[1] = '\0';
		ft_reset_term();
		ioctl(0, TIOCSTI, cp);
		ft_putstr("\b\b\033[0J");
		signal(SIGTSTP, SIG_DFL);
	}
}

void	ft_sig_cont(int i)
{
	t_term	*term;

	(void)i;
	init_term();
	signal(SIGTSTP, ft_sig_stop);
	term = ft_singleton();
	tcsetattr(0, TCSADRAIN, &(term->termios));
	winsize();
	refresh_screen();
}

void	init_signals(void)
{
	signal(SIGINT, ft_sig_int);
	signal(SIGQUIT, ft_sig_int);
	signal(SIGWINCH, sig_win_resize);
	signal(SIGTSTP, ft_sig_stop);
	signal(SIGCONT, ft_sig_cont);
}
