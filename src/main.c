/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/19 15:08:14 by aalliot           #+#    #+#             */
/*   Updated: 2016/11/14 17:13:34 by aalliot          ###   ########.fr       */
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

int		init_term(t_all *all)
{
	char	*res;

	ft_putstr_fd("\033[?1049h\033[H", all->fd);
	all->termios.c_lflag &= ~(ICANON | ECHO);
	all->termios.c_cc[VMIN] = 1;
	all->termios.c_cc[VTIME] = 0;
	if (ioctl(STDIN_FILENO, TIOCGWINSZ, (char*)&all->winsize) < 0)
	{
		ft_putstr_fd("TIOCGWINSZ error\n", 2);
		return (-1);
	}
	if (tcsetattr(0, TCSADRAIN, &all->termios) == -1)
	{
		ft_putstr_fd("TCSADRAIN error\n", 2);
		return (-1);
	}
	if (((all->mr = tgetstr("mr", NULL)) == NULL) ||
			((all->me = tgetstr("me", NULL)) == NULL) ||
			((all->us = tgetstr("us", NULL)) == NULL) ||
			((all->ue = tgetstr("ue", NULL)) == NULL) ||
			((all->cm = tgetstr("cm", NULL)) == NULL) ||
			((all->cl = tgetstr("cl", NULL)) == NULL))
	{
		ft_putstr_fd("tgetstr error\n", 2);
		return (-1);
	}
	tputs(all->cl, 0, ft_my_outc);
	if ((res = tgetstr("vi", NULL)) == NULL)
	{
		ft_putstr_fd("tgetstr vr error\n", 2);
		return (-1);
	}
	tputs(res, 0, ft_my_outc);
	return (0);
}

void		reset_term(t_all *all)
{
		char *res;

		ft_putstr_fd("\033[?1049l\033[0m", all->fd);
		if (tcgetattr(0, &all->termios) == -1)
			ft_putstr_fd("tcgetattr error\n", 2);
		all->termios.c_lflag |= (ICANON | ECHO);
		if (tcsetattr(0, 0, &all->termios) == -1)
			ft_putstr_fd("tcsetattr error\n", 2);
		res = tgetstr("ve", NULL);
		if (res == NULL)
			ft_putstr_fd("tgetstr error\n", 2);
		tputs(res, 0, ft_my_outc);
}

#define K_UP 4283163
#define K_DOWN 4348699
#define K_LEFT 4479771
#define K_RIGHT 4414235
#define K_ESC 27
#define K_RETURN 10
#define K_SPACE 32

void	ft_sig_int()
{
	t_all	*all;

	all = ft_singleton();
	reset_term(all);
	exit(0);
}

void	sigs_init()
{
	signal(SIGINT, ft_sig_int);
}

int		main()
{
	char	*term_name;
	t_all	*all;

	all = ft_singleton();

	// TODO: Catch Signals
	sigs_init();

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

	int		key;

	if (init_term(all) != -1)
	{
		while (42)
		{
			key = 0;
			read(0, &key, sizeof(int));
			printf("%d\n", key);
			if (key == K_UP)
				printf("Up key pressed\n");
			if (key == K_DOWN)
				printf("Down key pressed\n");
			if (key == K_LEFT)
				printf("Left key pressed\n");
			if (key == K_RIGHT)
				printf("Right key pressed\n");
			if (key == K_ESC)
				break;
		}
		reset_term(all);
	}
	return (0);
}
