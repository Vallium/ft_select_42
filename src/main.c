/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/19 15:08:14 by aalliot           #+#    #+#             */
/*   Updated: 2016/11/15 15:45:23 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

#include <stdio.h>

void		reset_term()
{
	char *res;
	t_term *term;

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

	free_entries();
}

int		main(int ac, char *av[])
{
	t_term	*term;

	term = ft_singleton();

	sigs_init();

	if (init_term() != -1)
	{
		init_entries(ac, av);
		while (42)
		{
			refresh_screen();
			if (key_press() == -1)
				break;
		}
		reset_term();
	}
	return (0);
}
