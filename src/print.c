/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 15:25:11 by aalliot           #+#    #+#             */
/*   Updated: 2016/11/16 15:25:13 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int		ft_my_outc(int c)
{
	t_term		*term;

	term = ft_singleton();
	write(term->fd, &c, 1);
	return (0);
}

void	print_entries()
{
	t_term	*term;
	int col;
	int	colcount;
	int row;

	term = ft_singleton();
	colcount = 0;
	row = 0;
	for (int z = 0; z < term->nb_entries; z++)
	{
		if (term->entries[z].visible == 0)
			continue;

		if (row > term->winsize.ws_row)
		{
			row = 0;
			colcount++;
		}
		col = colcount * (term->longest + 2);
		tputs(tgoto(term->cap[CM], col, row), 1, ft_my_outc);
		if (term->hover == z)
			tputs(term->cap[US], 0, ft_my_outc);
		if (term->entries[z].selected)
			tputs(term->cap[MR], 0, ft_my_outc);
		tputs(term->entries[z].name, 0, ft_my_outc);
		tputs(term->cap[ME], 0, ft_my_outc);
		row++;
	}
}

void	refresh_screen(void)
{
	t_term	*term;

	term = ft_singleton();

	tputs(term->cap[CL], 0, ft_my_outc);
	print_entries();
}
