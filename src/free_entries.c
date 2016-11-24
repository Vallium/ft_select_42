/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_entries.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 17:23:29 by aalliot           #+#    #+#             */
/*   Updated: 2016/11/24 17:23:30 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void		free_entries(void)
{
	t_term	*term;

	term = ft_singleton();
	while (--term->nb_entries >= 0)
		free(term->entries[term->nb_entries].name);
	free(term->entries);
}
