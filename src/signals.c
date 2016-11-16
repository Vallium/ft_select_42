/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 11:13:05 by aalliot           #+#    #+#             */
/*   Updated: 2016/11/16 11:13:09 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	sig_win_resize(int i)
{
	(void)i;
	winsize();
	refresh_screen();
}

void	ft_sig_int()
{
	reset_term();
	exit(0);
}

void	sigs_init()
{
	signal(SIGINT, ft_sig_int);
	signal(SIGQUIT, ft_sig_int);
	signal(SIGWINCH, sig_win_resize);
	// signal(SIGTSTP, ft_sig_stp);
	// signal(SIGCONT, ft_sig_cont);
}
