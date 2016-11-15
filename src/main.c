/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/19 15:08:14 by aalliot           #+#    #+#             */
/*   Updated: 2016/11/15 15:45:23 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

#include <stdio.h>

t_term	*ft_singleton(void)
{
	static t_term	term;

	return (&term);
}

int		ft_my_outc(int c)
{
	t_term		*term;

	term = ft_singleton();
	write(term->fd, &c, 1);
	return (0);
}

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
	if (ioctl(STDIN_FILENO, TIOCGWINSZ, (char*)&term->winsize) < 0)
	{
		ft_putstr_fd("TIOCGWINSZ error\n", 2);
		return (-1);
	}
	if (tcsetattr(0, TCSADRAIN, &term->termios) == -1)
	{
		ft_putstr_fd("TCSADRAIN error\n", 2);
		return (-1);
	}
	if (((term->cap[MR] = tgetstr("mr", NULL)) == NULL) ||
			((term->cap[ME] = tgetstr("me", NULL)) == NULL) ||
			((term->cap[US] = tgetstr("us", NULL)) == NULL) ||
			((term->cap[UE] = tgetstr("ue", NULL)) == NULL) ||
			((term->cap[CM] = tgetstr("cm", NULL)) == NULL) ||
			((term->cap[CL] = tgetstr("cl", NULL)) == NULL))
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
	return (0);
}

void		free_entries()
{
	t_term	*term;

	term = ft_singleton();
	while (--term->nb_entries >= 0)
		free(term->entries[term->nb_entries].name);
	free(term->entries);
}

void		reset_term()
{
	char *res;
	t_term *term;

	term = ft_singleton();
	ft_putstr_fd("\033[?1049l\033[0m", term->fd);
	if (tcgetattr(0, &term->termios) == -1)
		ft_putstr_fd("tcgetattr error\n", 2);
	term->termios.c_lflag |= (ICANON | ECHO);
	if (tcsetattr(0, 0, &term->termios) == -1)
		ft_putstr_fd("tcsetattr error\n", 2);
	res = tgetstr("ve", NULL);
	if (res == NULL)
		ft_putstr_fd("tgetstr error\n", 2);
	tputs(res, 0, ft_my_outc);

	free_entries();
}

void	ft_sig_int()
{
	reset_term();
	exit(0);
}

void	ft_error(char *err)
{
	reset_term();
	ft_putendl_fd(err, 2);
	exit(EXIT_FAILURE);
}

void	winsize(void)
{
	t_term	*term;

	term = ft_singleton();
	if (ioctl(STDIN_FILENO, TIOCGWINSZ, (char *)&term->winsize) < 0)
		ft_error("ft_select: error: Can't get terminal size.");
}

void	refresh_screen(void)
{
	t_term	*term;

	term = ft_singleton();

	tputs(term->cap[CL], 0, ft_my_outc);

	char *pos = tgetstr("cm", NULL);
	char *test = "~FT_SELECT BY AALLIOT~";
	int	center = (term->winsize.ws_col / 2) - (ft_strlen(test) / 2);
	int center2 = (term->winsize.ws_row / 2);
	tputs(tgoto(pos, center, center2), 1, ft_my_outc);
	tputs(test, 0, ft_my_outc);
}

void	sig_win_resize(int i)
{
	(void)i;
	winsize();
	refresh_screen();
}

void	sigs_init()
{
	signal(SIGINT, ft_sig_int);
	signal(SIGQUIT, ft_sig_int);
	signal(SIGWINCH, sig_win_resize);
	// signal(SIGTSTP, ft_sig_stp);
	// signal(SIGCONT, ft_sig_cont);
}

int		key_press()
{
	int		key;

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
		return (-1);
	return (0);
}

void	init_entries(int ac, char *av[])
{
	t_term	*term;
	int		i;

	term = ft_singleton();
	term->longest = 0;
	term->nb_entries = ac - 1;
	term->entries = (t_entry *)malloc(sizeof(t_entry) * term->nb_entries);
	i = 0;
	while (i < term->nb_entries)
	{
		term->entries[i].name = ft_strdup(av[i + 1]);
		term->entries[i].len = ft_strlen(av[i + 1]);
		term->entries[i].visible = 1;
		term->entries[i].selected = 0;
		if (term->entries[i].len > term->longest)
			term->longest = term->entries[i].len;
		i++;
	}

}

int		main(int ac, char *av[])
{
	t_term	*term;

	term = ft_singleton();

	sigs_init();

	if (init_term() != -1)
	{
		init_entries(ac, av);

		char *pos = tgetstr("cm", NULL);

		while (42)
		{
			// refresh_screen();
			int col;
			int	colcount = 0;
			int row = 0;
			for (int z = 0; z < term->nb_entries; z++)
			{
				col = colcount * (term->longest + 2);
				if (col + (term->longest + 2) > term->winsize.ws_col)
				{
					row++;
					colcount = 0;
					col = colcount * (term->longest + 2);
				}
				tputs(tgoto(pos, col, row), 1, ft_my_outc);
				tputs(term->entries[z].name, 0, ft_my_outc);
				colcount++;
			}
			if (key_press() == -1)
				break;
		}
		reset_term();
	}
	return (0);
}
