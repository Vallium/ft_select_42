/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_goto_left.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 12:35:37 by aalliot           #+#    #+#             */
/*   Updated: 2016/11/30 16:13:09 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	ft_goto_left(void)
{
	t_term	*term;
	t_entry	*entry;
	int		i;
	int		row;
	int		last_col_size;

	term = ft_singleton();
	if (term->total_column == 1)
		return ;
	i = 0;
	row = term->winsize.ws_row - term->padding_bottom;
	entry = (t_entry *)term->hover->content;
	if (entry->id - row < 0)
	{
		last_col_size = term->nb_entries % ((term->total_column - 1) * row);
		i = row - (last_col_size);
		if (entry->id - last_col_size >= 0)
			i -= entry->id - last_col_size + 1;
	}
	while (i < row)
	{
		term->hover = term->hover->prev;
		i++;
	}
}
