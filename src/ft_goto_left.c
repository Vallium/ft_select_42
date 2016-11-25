/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_goto_left.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 12:35:37 by aalliot           #+#    #+#             */
/*   Updated: 2016/11/25 12:35:39 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

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
