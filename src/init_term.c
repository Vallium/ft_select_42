/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_term.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 15:29:59 by aalliot           #+#    #+#             */
/*   Updated: 2016/11/30 16:26:08 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"
#include "stdio.h"

static int		init_term_norme(void)
{
	t_term	*term;
	char	*res;

	term = ft_singleton();
	if (tcsetattr(0, TCSADRAIN, &term->termios) == -1)
		ft_error("ft_select: TCSADRAIN error");
	if ((term->cap[MR] = tgetstr("mr", NULL)) == NULL ||
		(term->cap[ME] = tgetstr("me", NULL)) == NULL ||
		(term->cap[US] = tgetstr("us", NULL)) == NULL ||
		(term->cap[UE] = tgetstr("ue", NULL)) == NULL ||
		(term->cap[CM] = tgetstr("cm", NULL)) == NULL ||
		(term->cap[CL] = tgetstr("cl", NULL)) == NULL)
		ft_error("ft_select: tgetstr error");
	if ((res = tgetstr("vi", NULL)) == NULL)
		ft_error("tgetstr vi error\n");
	tputs(res, 0, ft_my_outc);
	return (1);
}

int				init_term(void)
{
	t_term	*term;
	char	*term_name;

	term = ft_singleton();
	term->fd = open(ttyname(STDIN_FILENO), O_WRONLY);
	if (term->fd == -1)
		ft_error_init("ft_select: Open error");
	term_name = getenv("TERM");
	if (term_name == NULL)
		ft_error_init("ft_select: getenv error");
	if (tgetent(NULL, term_name) == -1)
		ft_error_init("ft_select: getent error");
	if (tcgetattr(0, &term->termios) < 0)
		ft_error_init("ft_select: tcgetattr error");
	ft_putstr_fd("\033[?1049h\033[H", term->fd);
	term->termios.c_lflag &= ~(ICANON | ECHO);
	term->termios.c_cc[VMIN] = 1;
	term->termios.c_cc[VTIME] = 0;
	if (!init_term_norme())
		return (-1);
	term->padding_left = 0;
	winsize();
	return (0);
}
