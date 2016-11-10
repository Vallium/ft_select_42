/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/19 15:08:14 by aalliot           #+#    #+#             */
/*   Updated: 2016/11/10 18:16:24 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <term.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <string.h>

typedef struct termios t_termios;
typedef struct winsize t_winsize;

typedef struct	s_all
{
	t_termios	termios;
	t_winsize	winsize;
	char		*cl;
	char		*us;
	char		*ue;
	char		*rv;
	char		*mr;
	char		*me;
	char		*cm;
	int			fd;
}				t_all;

t_all	*ft_singleton(void)
{
	static t_all	all;

	return (&all);
}

int		ft_my_outc(int c)
{
	t_all		*all;

	all = ft_singleton();
	write(all->fd, &c, 1);
	return (0);
}

int		main()
{
	char	*term_name;
	t_all	*all;

	all = ft_singleton();

	// TODO: Catch Signals

	all->fd = open(ttyname(STDIN_FILENO), O_WRONLY);
	if (all->fd == -1)
		return (printf("Open error\n"));
	term_name = getenv("TERM");
	if (term_name == NULL)
		return (printf("getenv error\n"));
	if (tgetent(NULL, term_name) == -1)
		return (printf("getent error!\n"));
	if (tcgetattr(0, &all->termios) < 0)
		return(printf("tcgetattr error!\n"));

	// Init Term

	char	*res;

	ft_putstr_fd("\033[?1049h\033[H", all->fd);
	all->termios.c_lflag &= ~(ICANON | ECHO);
	all->termios.c_cc[VMIN] = 1;
	all->termios.c_cc[VTIME] = 0;
	if (ioctl(STDIN_FILENO, TIOCGWINSZ, (char*)&all->winsize) < 0)
	{
		ft_putstr_fd("TIOCGWINSZ error\n", 2);
		return (0);
	}
	if (tcsetattr(0, TCSADRAIN, &all->termios) == -1)
	{
		ft_putstr_fd("TCSADRAIN error\n", 2);
		return (0);
	}
	if (((all->mr = tgetstr("mr", NULL)) == NULL) ||
			((all->me = tgetstr("me", NULL)) == NULL) ||
			((all->us = tgetstr("us", NULL)) == NULL) ||
			((all->ue = tgetstr("ue", NULL)) == NULL) ||
			((all->cm = tgetstr("cm", NULL)) == NULL) ||
			((all->cl = tgetstr("cl", NULL)) == NULL))
	{
		ft_putstr_fd("tgetstr error\n", 2);
		return (0);
	}
	tputs(all->cl, 0, ft_my_outc);
	if ((res = tgetstr("vi", NULL)) == NULL)
	{
		ft_putstr_fd("tgetstr vr error\n", 2);
		return (0);
	}
	tputs(res, 0, ft_my_outc);
	return (0);
}
