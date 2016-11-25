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
		ft_reset_term();
	}
	return (0);
}
