/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/19 15:08:14 by aalliot           #+#    #+#             */
/*   Updated: 2016/11/09 15:50:56 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <term.h>
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

	term.c_lflag &= ~(ICANON);
	term.c_lflag &= ~(ECHO);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;

	if (tcsetattr(0, TCSADRAIN, &term) == -1)
		return(printf("tcsetattr error!\n"));


	char	key[3];

	while (42)
	{
		bzero(key, 3);
		read(0, key, 3);
		printf("%d", key[0]);
		printf("%d", key[1]);
		printf("%d\n", key[2]);

		if (key[0] == 27)
		{
			if (key[1] == 91)
			{
					if (key[2] == 65)
						printf("Up\n");
					else if (key[2] == 66)
						printf("Down\n");
					else if (key[2] == 68)
						printf("Left\n");
					else if (key[2] == 67)
						printf("Right\n");
			}
			else if (key[1] == 0)
				return (-1);
		}
	}

	if (tcsetattr(0, TCSADRAIN, &bu_term) == -1)
		return(printf("tcsetattr error!\n"));
	return (0);
}
