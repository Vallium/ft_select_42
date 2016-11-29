/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_do_space.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 12:36:22 by aalliot           #+#    #+#             */
/*   Updated: 2016/11/29 12:39:00 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void		ft_do_space(void)
{
	t_term	*term;
	int		i;

	term = ft_singleton();
	i = ((t_entry*)term->hover->content)->selected ? 0: 1;
	((t_entry*)term->hover->content)->selected = i;
	ft_goto_down();
}
