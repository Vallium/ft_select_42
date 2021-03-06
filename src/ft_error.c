/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 15:38:55 by aalliot           #+#    #+#             */
/*   Updated: 2016/11/24 15:15:49 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	ft_error(char *err)
{
	ft_reset_term();
	ft_putendl_fd(err, 2);
	exit(EXIT_FAILURE);
}

void	ft_error_init(char *err)
{
	ft_putendl_fd(err, 2);
	exit(EXIT_FAILURE);
}
