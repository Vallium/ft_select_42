/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/19 15:08:14 by aalliot           #+#    #+#             */
/*   Updated: 2016/11/30 16:13:52 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int		main(int ac, char *av[])
{
	int		key_press_ret;

	if (ac < 2)
		return (0);
	init_signals();
	if (init_term() != -1)
	{
		init_entries(ac, av);
		refresh_screen();
		while (42)
		{
			key_press_ret = key_press();
			if (!key_press_ret)
				continue ;
			if (key_press_ret == -1)
				break ;
			refresh_screen();
		}
		ft_reset_term();
		free_entries();
	}
	return (0);
}
