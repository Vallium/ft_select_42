/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refresh_screen.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 13:35:37 by aalliot           #+#    #+#             */
/*   Updated: 2016/11/30 16:33:01 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void			scroll_bar(void)
{
	t_term	*term;
	int		size_col;
	int		i;
	int		left;

	term = ft_singleton();
	size_col = term->winsize.ws_col / term->total_column;
	left = term->winsize.ws_col % term->total_column;
	i = 0;
	if (size_col == 0)
		return ;
	tputs(tgoto(term->cap[CM], left / 2, term->winsize.ws_row), 1, ft_my_outc);
	tputs(term->cap[MR], 0, ft_my_outc);
	while (i < term->winsize.ws_col - left)
	{
		if (i >= (term->padding_left * size_col) && \
				i <= (term->padding_left + term->nb_column) * size_col)
			tputs("#", 0, ft_my_outc);
		else
			tputs("-", 0, ft_my_outc);
		i++;
	}
	tputs(term->cap[ME], 0, ft_my_outc);
}

static void		too_small(void)
{
	t_term	*term;
	int		row;
	int		col;

	term = ft_singleton();
	row = 0;
	while (row < term->winsize.ws_row)
	{
		col = 0;
		while (col < term->winsize.ws_col)
		{
			tputs(tgoto(term->cap[CM], col, row), 1, ft_my_outc);
			tputs("X", 0, ft_my_outc);
			col++;
		}
		row++;
	}
	return ;
}

void			refresh_screen(void)
{
	t_term	*term;

	term = ft_singleton();
	term->padding_bottom = 1;
	tputs(term->cap[CL], 0, ft_my_outc);
	if (term->winsize.ws_col < term->longest + 2)
		return (too_small());
	refresh_padding_left();
	if (term->nb_column < term->total_column)
		scroll_bar();
	print_entries();
}
