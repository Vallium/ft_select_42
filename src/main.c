/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/19 15:08:14 by aalliot           #+#    #+#             */
/*   Updated: 2016/11/09 17:04:50 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <term.h>
#include <sys/ioctl.h>
#include <string.h>
char *byte_to_binary(int x)
{
	static char b[9];
	b[0] = '\0';

	int z;
	for (z = 128; z > 0; z >>= 1)
	{
		strcat(b, ((x & z) == z) ? "1" : "0");
	}

	return b;
}

int		ft_putchar(int c)
{
	write(1, &c, 1);
	return (0);
}

int		main()
{
	char			*name_term;
	struct termios	term;
	struct termios	bu_term;

	if ((name_term = getenv("TERM")) == NULL)
		return (printf("getenv error!\n"));
	if (tgetent(NULL, name_term) <= 0)
		return (printf("getent error!\n"));

	if (tcgetattr(0, &term) < 0)
		return(printf("tcgetattr error!\n"));
	
	if (tcgetattr(0, &bu_term) < 0)
		return(printf("tcgetattr error!\n"));

	term.c_lflag &= ~(ICANON | ECHO | ECHOE | ECHOK | ECHONL);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;

	if (tcsetattr(0, TCSADRAIN, &term) == -1)
		return(printf("tcsetattr error!\n"));


	char	key[3];
	char	*id;

		struct winsize w;
	//if ((id = tgetstr("cl", NULL)) == NULL)
	//	return(printf("On peut niquer no meres!\n"));
	//tputs(id, 0, ft_putchar);

	if ((id = tgetstr("ti", NULL)) == NULL)
		return (printf("tgetstr(ti) failed\n"));
	tputs(id, 0, ft_putchar);


	while (42)
	{
	    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

	    //printf ("lines %d\n", w.ws_row);
	   // printf ("columns %d\n", w.ws_col);

		bzero(key, 3);
		read(0, key, 3);

		if (key[0] == 27)
		{
			if (key[1] == 91)
			{
					if (key[2] == 65)
						tputs("Up\n", 0, ft_putchar);
					else if (key[2] == 66)
						tputs("Down\n", 0, ft_putchar);
					else if (key[2] == 68)
						tputs("Left\n", 0, ft_putchar);
					else if (key[2] == 67)
						tputs("Right\n", 0, ft_putchar);
			}
			else if (key[1] == 0)
			{
				if ((id = tgetstr("cl", NULL)) == NULL)
					return(printf("On peut niquer no meres!\n"));
				tputs(id, 0, ft_putchar);
				if (tcsetattr(0, TCSADRAIN, &bu_term) == -1)
					return(printf("tcsetattr error!\n"));
				return (-1);
			}
		}
	}

	return (0);
}
