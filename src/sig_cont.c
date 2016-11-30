/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_cont.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 16:47:04 by aalliot           #+#    #+#             */
/*   Updated: 2016/11/30 16:47:23 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	sig_cont(int i)
{
	t_term	*term;

	(void)i;
	init_term();
	signal(SIGTSTP, sig_tstp);
	term = ft_singleton();
	tcsetattr(0, TCSADRAIN, &(term->termios));
	winsize();
	refresh_screen();
}
