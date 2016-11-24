/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 15:22:06 by aalliot           #+#    #+#             */
/*   Updated: 2016/11/24 15:37:01 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void ft_goto_up()
{
	t_term	*term;
	int		i;

	term = ft_singleton();
	i = term->hover - 1;
	if (i < 0)
		i = term->total_entries - 1;
	while (i != term->hover && !term->entries[i].visible)
	{
		if (i < 0)
			i = term->total_entries - 1;
		i--;
	}
	term->hover = i;
}

void	ft_goto_down()
{
	t_term	*term;
	int		i;

	term = ft_singleton();
	i = term->hover + 1;
	if (i >= term->total_entries)
		i = 0;
	while (i != term->hover && !term->entries[i].visible)
	{
		if (i >= term->total_entries)
			i = 0;
		i++;
	}
	term->hover = i;
}

void	ft_goto_left()
{
	t_term	*term;
	int		jmp;

	term = ft_singleton();
	jmp = term->winsize.ws_row;
	if (term->hover - jmp < 0)
	{
		jmp -= (term->nb_entries % term->winsize.ws_row);
		term->hover = term->total_entries - 1;
	}
	while (jmp)
	{
		if (term->entries[term->hover].visible)
			jmp--;
		term->hover--;
	}
}

static void	goto_start(void)
{
	t_term	*term;
	int	i;

	term = ft_singleton();
	i = term->hover - ((term->padding_left + 1) * term->winsize.ws_row);
	term->hover = (i % (term->nb_column + 1));
	//term->padding_left = 0;
}

void	ft_goto_right(void)
{
	t_term	*term;
	int		i;

	term = ft_singleton();
	i = 0;
	while (i < term->winsize.ws_row)
	{
		term->hover++;
		if (term->hover >= term->total_entries)
			goto_start();
		if (term->entries[term->hover].visible)
			i++;
	}
}

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
