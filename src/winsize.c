/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   winsize.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 15:42:37 by aalliot           #+#    #+#             */
/*   Updated: 2016/11/16 15:42:38 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	winsize(void)
{
	t_term	*term;

	term = ft_singleton();
	if (ioctl(STDIN_FILENO, TIOCGWINSZ, (char *)&term->winsize) < 0)
		ft_error("ft_select: error: Can't get terminal size.");
	if (term->nb_entries - 2)
	{
		term->nb_column = term->winsize.ws_col / (term->longest + 2);
		term->total_column = (term->nb_entries / (term->winsize.ws_row - \
			term->padding_bottom)) + 1;
	}
}
