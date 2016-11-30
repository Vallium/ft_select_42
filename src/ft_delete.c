/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delete.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 12:39:59 by aalliot           #+#    #+#             */
/*   Updated: 2016/11/30 16:12:48 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void		free_entry(void *entry, size_t size)
{
	free(((t_entry *)entry)->name);
	((t_entry *)entry)->name = NULL;
	free(entry);
	entry = NULL;
	(void)size;
}

void			ft_delete(void)
{
	t_term	*term;
	t_lstd	*next;

	term = ft_singleton();
	term->nb_entries--;
	next = term->hover->next;
	if (term->hover == term->entries)
		term->entries = next;
	ft_lstddelone(&term->hover, free_entry);
	if (term->nb_entries == 0)
		sig_exit(0);
	term->hover = next;
	winsize();
}
