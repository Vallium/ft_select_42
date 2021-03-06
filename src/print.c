/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 15:25:11 by aalliot           #+#    #+#             */
/*   Updated: 2016/11/30 16:27:52 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void		print_entry(void)
{
	t_term	*term;
	t_entry	*entry;

	term = ft_singleton();
	entry = (t_entry *)term->entries->content;
	if ((t_entry *)term->hover->content == entry)
		tputs(term->cap[US], 0, ft_my_outc);
	if (entry->selected)
		tputs(term->cap[MR], 0, ft_my_outc);
	tputs(entry->name, 0, ft_my_outc);
	tputs(term->cap[ME], 0, ft_my_outc);
}

void			print_entries(void)
{
	t_term	*term;
	t_entry	*entry;
	int		i;
	int		col;
	int		row;

	term = ft_singleton();
	i = 0;
	col = 0;
	row = term->winsize.ws_row - term->padding_bottom;
	while (i < term->nb_entries)
	{
		entry = (t_entry *)term->entries->content;
		if (i && i % row == 0)
			col++;
		if (col >= term->padding_left && col \
				- term->padding_left < term->nb_column)
		{
			tputs(tgoto(term->cap[CM], (col - term->padding_left) \
						* (term->longest + 2), i % row), 1, ft_my_outc);
			print_entry();
		}
		term->entries = term->entries->next;
		entry->id = i++;
	}
}
