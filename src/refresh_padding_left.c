/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refresh_padding_left.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 13:38:43 by aalliot           #+#    #+#             */
/*   Updated: 2016/11/30 16:24:51 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static int		set_padding_left(t_entry *entry, int first, int last)
{
	t_term	*term;

	term = ft_singleton();
	if (term->total_column < term->nb_column)
	{
		term->padding_left = 0;
		return (0);
	}
	else if (term->padding_left < 0)
		term->padding_left = term->total_column - term->nb_column;
	else if (term->padding_left > term->total_column - term->nb_column)
		term->padding_left = 0;
	else if (entry->id < first)
		term->padding_left--;
	else if (entry->id > last)
		term->padding_left++;
	else
		return (0);
	return (1);
}

void			refresh_padding_left(void)
{
	t_term	*term;
	t_entry	*entry;
	int		last;
	int		first;
	int		row;

	term = ft_singleton();
	entry = (t_entry *)term->hover->content;
	row = term->winsize.ws_row - term->padding_bottom;
	while (42)
	{
		first = term->padding_left * row;
		last = (term->padding_left + term->nb_column) * row - 1;
		if (!set_padding_left(entry, first, last))
			break ;
	}
}
