/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/08 20:30:22 by aalliot           #+#    #+#             */
/*   Updated: 2015/12/08 20:32:54 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_strrev(char *str)
{
	int		len;
	int		i;
	char	tmp;

	len = ft_strlen(str) - 1;
	i = 0;
	while (i < len)
	{
		tmp = str[i];
		str[i++] = str[len];
		str[len--] = tmp;
	}
}
