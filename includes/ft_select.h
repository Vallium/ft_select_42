/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 16:25:42 by aalliot           #+#    #+#             */
/*   Updated: 2016/11/29 13:44:17 by aalliot          ###   ########.fr       */
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
# define K_DELETE 2117294875
# define K_BACKSPACE 127

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
	short			selected;
	int				id;
}					t_entry;

typedef struct	s_term
{
	t_termios	termios;
	t_winsize	winsize;
	char		*cap[7];
	int			fd;
	t_lstd		*entries;
	int			nb_entries;
	t_lstd		*hover;
	int			longest;
	int			nb_column;
	int			total_column;
	int			padding_left;
	int			padding_bottom;
}				t_term;

t_term	*ft_singleton(void);

int		init_term();
void	init_entries(int ac, char *av[]);

void	sig_win_resize(int i);
void	ft_sig_int();
void	init_signals();
void	sig_exit(int i);

void	ft_goto_previous();
void	ft_goto_next();

void	ft_goto_up();
void	ft_goto_down();
void	ft_goto_left();
void	ft_goto_right();
void	ft_do_space();
void	ft_delete();
int		return_result(void);
int		key_press();

int		ft_my_outc(int c);
void	print_entries();
void	refresh_screen(void);
void	refresh_padding_left();

void	winsize(void);

void	free_entries();

void	ft_error(char *err);

void	ft_reset_term(void);

#endif
