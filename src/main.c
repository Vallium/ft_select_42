/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/19 15:08:14 by aalliot           #+#    #+#             */
/*   Updated: 2016/11/29 18:20:11 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"
#include <stdio.h>

/*
 *	TODO: cursor not appear wheb ctrl+z
 *	TODO: debug returned values
 *	TODO: not working as expected when env -i
 *	TODO: do not save args like empty string
**/

int		main(int ac, char *av[])
{
	if (ac < 2)
		return (0);
	init_signals();

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
		free_entries();
	}
	return (0);
}
