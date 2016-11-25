/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 15:22:06 by aalliot           #+#    #+#             */
/*   Updated: 2016/11/25 12:35:50 by aalliot          ###   ########.fr       */
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
		//term->hover = (term->hover > 0) ? term->hover - 1 : term->nb_entries - 1;
	if (key == K_DOWN)
		ft_goto_down();
		//term->hover = (term->hover < term->nb_entries - 1) ? term->hover + 1 : 0;
	if (key == K_LEFT) 
		ft_goto_left();
	if (key == K_RIGHT)
		ft_goto_right();
		// term->hover += term->winsize.ws_row + 1;
	if (key == K_SPACE)
	{
		term->entries[term->hover].selected = term->entries[term->hover].selected ? 0 : 1;
		term->hover = (term->hover < term->nb_entries - 1) ? term->hover + 1 : 0;
	}
	if (key == K_DELETE || key == K_BACKSPACE)
	{
		term->entries[term->hover].visible = 0;
		term->nb_entries--;
		if (term->nb_entries == 0)
			return (-1);
		term->hover = (term->hover < term->nb_entries - 1) ? term->hover + 1 : 0;
	}
	if (key == K_ESC)
		return (-1);
	return (0);
}

