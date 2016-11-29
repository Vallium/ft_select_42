/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_goto_right.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 12:35:41 by aalliot           #+#    #+#             */
/*   Updated: 2016/11/29 12:31:14 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	ft_goto_right(void)
{
	t_term	*term;
	t_entry	*entry;
	int		i;
	int		row;

	term = ft_singleton();
	if (term->total_column == 1)
		return ;
	i = 0;
	row = term->winsize.ws_row - term->padding_bottom;
	entry = (t_entry *)term->hover->content;
	if (entry->id + row >= term->nb_entries)
	{
		i = row - (term->nb_entries % ((term->total_column - 1) * row));
		if (entry->id + row < row * term->total_column)
			i -= (row - (entry->id % row)) - 1;
	}
	while (i < row)
	{
		term->hover = term->hover->next;
		i++;
	}
}
