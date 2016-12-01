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

void	init_signals(void)
{
	signal(SIGINT, sig_exit);
	signal(SIGQUIT, sig_exit);
	signal(SIGABRT, sig_exit);
	signal(SIGKILL, sig_exit);
	signal(SIGWINCH, sig_winch);
	signal(SIGTSTP, sig_tstp);
	signal(SIGCONT, sig_cont);
}
