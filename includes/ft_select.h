/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 16:25:42 by aalliot           #+#    #+#             */
/*   Updated: 2016/11/15 16:31:44 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H

# include "libft.h"
# include <stdlib.h>
# include <termios.h>
# include <unistd.h>
# include <term.h>
# include <sys/ioctl.h>
# include <fcntl.h>
# include <string.h>


# define K_UP 4283163
# define K_DOWN 4348699
# define K_LEFT 4479771
# define K_RIGHT 4414235
# define K_ESC 27
# define K_RETURN 10
# define K_SPACE 32

enum cap {CL, US, UE, RV, MR, ME, CM};

typedef struct termios t_termios;
typedef struct winsize t_winsize;

typedef struct		s_pos
{
	unsigned int	col;
	unsigned int	row;
}					t_pos;

typedef struct		s_entry
{
	char			*name;
	int				len;
	short			visible;
	short			selected;
	t_pos			pos;
}					t_entry;

typedef struct	s_term
{
	t_termios	termios;
	t_winsize	winsize;
	char		*cap[7];
	int			fd;
	t_entry		*entries;
	int			nb_entries;
	int			longest;
	int			hover;
}				t_term;

#endif
