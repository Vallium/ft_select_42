/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_entries.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 17:23:29 by aalliot           #+#    #+#             */
/*   Updated: 2016/11/29 12:16:45 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void delete_entries(void *content, size_t size)
{
	t_entry *entry;

	entry = (t_entry *)content;
	free(entry->name);
	entry->name = NULL;
	free(entry);
	entry = NULL;
	(void)size;
}

void		free_entries(void)
{
	t_term	*term;
	int		i;
	t_lstd	*next;

	term = ft_singleton();
	i = 0;
	while (i < term->nb_entries)
	{
		next = term->entries->next;
		ft_lstddelone(&term->entries, delete_entries);
		term->entries = next;
		i++;
	}
}
