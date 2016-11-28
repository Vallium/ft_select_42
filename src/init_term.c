/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_term.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 15:29:59 by aalliot           #+#    #+#             */
/*   Updated: 2016/11/24 15:16:16 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"
#include "stdio.h"

int		init_term()
{	
	char	*term_name;
	char	*res;

	t_term *term;

	term = ft_singleton();

	term->fd = open(ttyname(STDIN_FILENO), O_WRONLY);
	if (term->fd == -1)
		return (printf("Open error\n"));
	term_name = getenv("TERM");
	if (term_name == NULL)
		return (printf("getenv error\n"));
	if (tgetent(NULL, term_name) == -1)
		return (printf("getent error!\n"));
	if (tcgetattr(0, &term->termios) < 0)
		return(printf("tcgetattr error!\n"));
	ft_putstr_fd("\033[?1049h\033[H", term->fd);
	term->termios.c_lflag &= ~(ICANON | ECHO);
	term->termios.c_cc[VMIN] = 1;
	term->termios.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSADRAIN, &term->termios) == -1)
	{
		ft_putstr_fd("TCSADRAIN error\n", 2);
		return (-1);
	}
	if ((term->cap[MR] = tgetstr("mr", NULL)) == NULL ||
		(term->cap[ME] = tgetstr("me", NULL)) == NULL ||
		(term->cap[US] = tgetstr("us", NULL)) == NULL ||
		(term->cap[UE] = tgetstr("ue", NULL)) == NULL ||
		(term->cap[CM] = tgetstr("cm", NULL)) == NULL ||
		(term->cap[CL] = tgetstr("cl", NULL)) == NULL)
	{
		ft_putstr_fd("tgetstr error\n", 2);
		return (-1);
	}
	// tputs(term->cl, 0, ft_my_outc);
	if ((res = tgetstr("vi", NULL)) == NULL)
	{
		ft_putstr_fd("tgetstr vr error\n", 2);
		return (-1);
	}
	tputs(res, 0, ft_my_outc);
	term->padding_left = 0;
	winsize();
	return (0);
}