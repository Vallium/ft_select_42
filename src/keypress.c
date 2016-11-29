/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 15:22:06 by aalliot           #+#    #+#             */
/*   Updated: 2016/11/29 12:36:06 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int		key_press()
{
	int		key;
	t_term	*term;

	key = 0;
	term = ft_singleton();
	read(0, &key, sizeof(int));
	if (key == K_UP)
		ft_goto_up();
	if (key == K_DOWN)
		ft_goto_down();
	if (key == K_LEFT) 
		ft_goto_left();
	if (key == K_RIGHT)
		ft_goto_right();
	if (key == K_SPACE)
		ft_do_space();
	if (key == K_DELETE || key == K_BACKSPACE)
		ft_delete();
	if (key == K_ESC)
		return (-1);
	return (0);
}

