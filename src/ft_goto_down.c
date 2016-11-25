/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_goto_down.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 12:35:33 by aalliot           #+#    #+#             */
/*   Updated: 2016/11/25 12:35:35 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	ft_goto_down()
{
	t_term	*term;
	int		i;

	term = ft_singleton();
	i = term->hover + 1;
	if (i >= term->total_entries)
		i = 0;
	while (i != term->hover && !term->entries[i].visible)
	{
		if (i >= term->total_entries)
			i = 0;
		i++;
	}
	term->hover = i;
}
