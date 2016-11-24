/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_entries.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 17:27:11 by aalliot           #+#    #+#             */
/*   Updated: 2016/11/24 17:28:13 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	init_entries(int ac, char *av[])
{
	t_term	*term;
	int		i;

	term = ft_singleton();
	term->longest = 0;
	term->nb_entries = ac - 1;
	term->total_entries = term->nb_entries;
	term->hover = 0;
	term->entries = (t_entry *)malloc(sizeof(t_entry) * term->nb_entries);
	if (term->entries == NULL)
		ft_error("ft_select: error: malloc entries failed");
	i = 0;
	while (i < term->nb_entries)
	{
		term->entries[i].name = ft_strdup(av[i + 1]);
		term->entries[i].len = ft_strlen(av[i + 1]);
		term->entries[i].visible = 1;
		term->entries[i].selected = 0;
		if (term->entries[i].len > term->longest)
			term->longest = term->entries[i].len;
		i++;
	}
}
