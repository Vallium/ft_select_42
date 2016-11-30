/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_tstp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 16:47:34 by aalliot           #+#    #+#             */
/*   Updated: 2016/11/30 16:47:50 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"
#include <signal.h>

void	sig_tstp(int i)
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
