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

void	print_entry(int i, int *colcount, int *row, int nbrow)
{
	int		col;
	t_term	*term;

	term = ft_singleton();
	if (term->entries[i].visible == 0)
		return ;
	if (*row >= nbrow)
	{
		*row = 0;
		(*colcount)++;
	}
	if (*colcount >= term->nb_column)
		return ;
	col = *colcount * (term->longest + 2);
	tputs(tgoto(term->cap[CM], col, *row), 1, ft_my_outc);
	if (term->hover == i)
		tputs(term->cap[US], 0, ft_my_outc);
	if (term->entries[i].selected)
		tputs(term->cap[MR], 0, ft_my_outc);
	tputs(term->entries[i].name, 0, ft_my_outc);
	tputs(term->cap[ME], 0, ft_my_outc);
	(*row)++;
}

int	jump_hidden(t_term *term)
{
	int tojmp;
	int	i;
	int	ret;

	tojmp = term->padding_left * term->winsize.ws_row;
	i = 0;
	ret = 0;
	while (i < tojmp)
	{
		if (term->entries[ret].visible)
			i++;
		ret++;
	}
	return (ret);
}

void		print_entries(void)
{
	t_term	*term;
	int		colcount;
	int		row;
	int		i;
	int		nbrow;

	term = ft_singleton();
	colcount = 0;
	row = 0;
	i = jump_hidden(term);
	nbrow = term->winsize.ws_row;
	if (tgetflag("hs"))
		nbrow = term->winsize.ws_row - tgetnum("ws");
	while (i < term->total_entries)
	{
		print_entry(i, &colcount, &row, nbrow);
		i++;
	}
}

// void	print_entries()
// {
// 	t_term	*term;
// 	int col;
// 	int	colcount;
// 	int row;

// 	term = ft_singleton();
// 	colcount = 0;
// 	row = 0;
// 	for (int z = 0; z < term->nb_entries; z++)
// 	{
// 		if (term->entries[z].visible == 0)
// 			continue;

// 		if (row > term->winsize.ws_row)
// 		{
// 			row = 0;
// 			colcount++;
// 		}
// 		col = colcount * (term->longest + 2);
// 		tputs(tgoto(term->cap[CM], col, row), 1, ft_my_outc);
// 		if (term->hover == z)
// 			tputs(term->cap[US], 0, ft_my_outc);
// 		if (term->entries[z].selected)
// 			tputs(term->cap[MR], 0, ft_my_outc);
// 		tputs(term->entries[z].name, 0, ft_my_outc);
// 		tputs(term->cap[ME], 0, ft_my_outc);
// 		row++;
// 	}
// }

void	refresh_padding_left(void)
{
	t_term	*term;

	term = ft_singleton();
	while (1)
		if (term->total_column <= term->nb_column)
		{
			term->padding_left = 0;
			break ;
		}
		else if (term->hover <= (term->padding_left * term->winsize.ws_row) - 1)
			term->padding_left--;
		else if (term->hover >= (term->nb_column * term->winsize.ws_row) + (term->padding_left * term->winsize.ws_row))
			term->padding_left++;
		else
			break ;
}

void	refresh_screen(void)
{
	t_term	*term;

	term = ft_singleton();

	tputs(term->cap[CL], 0, ft_my_outc);
	refresh_padding_left();
	print_entries();
}
