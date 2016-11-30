/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reset_term.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 17:20:13 by aalliot           #+#    #+#             */
/*   Updated: 2016/11/24 17:20:15 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void		ft_reset_term(void)
{
	char	*res;
	t_term	*term;

	term = ft_singleton();
	ft_putstr_fd("\033[?1049l\033[0m", term->fd);
	if (tcgetattr(0, &term->termios) == -1)
		ft_putstr_fd("tcgetattr error\n", 2);
	term->termios.c_lflag |= (ICANON | ECHO);
	if (tcsetattr(0, 0, &term->termios) == -1)
		ft_putstr_fd("tcsetattr error\n", 2);
	res = tgetstr("ve", NULL);
	if (res == NULL)
		ft_putstr_fd("tgetstr error\n", 2);
	tputs(res, 0, ft_my_outc);
}
