/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refresh_padding_left.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 13:38:43 by aalliot           #+#    #+#             */
/*   Updated: 2016/11/29 13:45:04 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void		refresh_padding_left(void)
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
		if (term->total_column < term->nb_column)
		{
			term->padding_left = 0;
			break ;
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
			break;
	}
}
