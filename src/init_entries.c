/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_entries.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 17:27:11 by aalliot           #+#    #+#             */
/*   Updated: 2016/11/29 12:32:52 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void		set_entry(char *av, int i)
{
	t_entry	entry;
	t_term	*term;
	t_lstd	*tmp;
	int		len;

	term = ft_singleton();
	len = ft_strlen(av);
	entry.name = ft_strdup(av);
	entry.selected = 0;
	entry.id = i - 1;
	if (!(tmp = ft_lstdnew(&entry, sizeof(t_entry))))
		ft_error("ft_select: entries failed");
	ft_lstdadd(&(term->entries), tmp);
	if (len > term->longest)
		term->longest = len;
}

void			init_entries(int ac, char *av[])
{
	t_term	*term;
	int		i;

	term = ft_singleton();
	term->longest = 0;
	term->nb_entries = ac - 1;
	term->entries = NULL;
	term->padding_left = 0;
	i = 1;
	while (i < ac)
	{
		if (ft_strcmp(av[i], ""))
			set_entry(av[i], i);
		else
			term->nb_entries--;
		i++;
	}
	if (!term->nb_entries)
		ft_error("ft_select: invalid args");
	term->hover = term->entries;
	winsize();
}
