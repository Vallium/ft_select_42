/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 15:22:06 by aalliot           #+#    #+#             */
/*   Updated: 2016/11/16 15:22:09 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void ft_goto_previous()
{
	t_term	*term;
	int 	i;

	term = ft_singleton();
	i = term->hover;
	while (i >= 0)
	{
		i--;
		if (term->entries[i].visible == 1)
		{
			term->hover = i;
			return ;
		}
	}
	term->hover = term->nb_entries - 1;
	
}

void	ft_goto_next()
{
	t_term	*term;
	int 	i;

	term = ft_singleton();
	i = term->hover;
	while (i < term->nb_entries)
	{
		i++;
		if (term->entries[i].visible == 1)
		{
			term->hover = i;
			return ;
		}
	}
	term->hover = 0;
}

int		key_press()
{
	int		key;
	t_term	*term;

	key = 0;
	term = ft_singleton();
	read(0, &key, sizeof(int));
	if (key == K_UP)
		ft_goto_previous();
		//term->hover = (term->hover > 0) ? term->hover - 1 : term->nb_entries - 1;
	if (key == K_DOWN)
		term->hover = (term->hover < term->nb_entries - 1) ? term->hover + 1 : 0;
	if (key == K_LEFT) 
		term->hover -= term->winsize.ws_row + 1;
	if (key == K_RIGHT)
		term->hover += term->winsize.ws_row + 1;
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