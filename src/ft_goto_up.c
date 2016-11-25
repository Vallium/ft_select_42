/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_goto_up.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 12:35:27 by aalliot           #+#    #+#             */
/*   Updated: 2016/11/25 12:35:30 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void ft_goto_up()
{
	t_term	*term;
	int		i;

	term = ft_singleton();
	i = term->hover - 1;
	if (i < 0)
		i = term->total_entries - 1;
	while (i != term->hover && !term->entries[i].visible)
	{
		if (i < 0)
			i = term->total_entries - 1;
		i--;
	}
	term->hover = i;
}
