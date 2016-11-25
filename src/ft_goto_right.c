/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_goto_right.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 12:35:41 by aalliot           #+#    #+#             */
/*   Updated: 2016/11/25 12:35:44 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

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
