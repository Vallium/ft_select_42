/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 15:22:06 by aalliot           #+#    #+#             */
/*   Updated: 2016/11/30 16:14:46 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static int		get_key(t_term *term)
{
	int		key;

	key = 0;
	read(0, &key, sizeof(int));
	if (term->winsize.ws_col < term->longest)
		return (0);
	if (key == K_UP)
		ft_goto_up();
	else if (key == K_DOWN)
		ft_goto_down();
	else if (key == K_LEFT)
		ft_goto_left();
	else if (key == K_RIGHT)
		ft_goto_right();
	else if (key == K_SPACE)
		ft_do_space();
	else if (key == K_RETURN)
		return (return_result());
	else if (key == K_DELETE || key == K_BACKSPACE)
		ft_delete();
	else if (key == K_ESC)
		return (-1);
	else
		return (0);
	return (1);
}

int				key_press(void)
{
	t_term	*term;

	term = ft_singleton();
	return (get_key(term));
}
