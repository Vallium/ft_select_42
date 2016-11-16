/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 15:35:44 by aalliot           #+#    #+#             */
/*   Updated: 2016/11/16 15:35:45 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void		free_entries()
{
	t_term	*term;

	term = ft_singleton();
	while (--term->nb_entries >= 0)
		free(term->entries[term->nb_entries].name);
	free(term->entries);
}
