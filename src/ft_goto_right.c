/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_goto_right.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 12:35:41 by aalliot           #+#    #+#             */
/*   Updated: 2016/11/29 12:31:14 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	ft_goto_right(void)
{
	t_term	*term;
	int		i;

	term = ft_singleton();
	i = 0;
	while (i < term->winsize.ws_row - term->padding_bottom)
	{
		term->hover = term->hover->next;
		i++;
	}
}
