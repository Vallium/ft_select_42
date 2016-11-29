/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_entries.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 15:57:47 by aalliot           #+#    #+#             */
/*   Updated: 2016/11/29 15:57:49 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_select.h>

int	return_result(void)
{
	t_term	*term;
	int		i;
	t_entry	*entry;
	int		space;

	term = ft_singleton();
	i = 0;
	space = 0;
	ft_reset_term();
			ft_putstr("test");

	while (i < term->nb_entries)
	{
		entry = (t_entry *)term->entries->content;
		if (entry->selected)
		{
			if (space)
				ft_putchar(' ');
			space = 1;
			ft_putstr(entry->name);
		}
		term->entries = term->entries->next;
		i++;
	}
	return (-1);
}

