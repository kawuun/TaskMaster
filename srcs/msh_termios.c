/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_termios.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvdovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/22 21:23:34 by dvdovenk          #+#    #+#             */
/*   Updated: 2017/07/22 21:23:36 by dvdovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_lib.h"

static void	getentry(char *tty)
{
	int		res;
	char	buf[1024];

	if ((res = tgetent(buf, tty)) < 1)
	{
		if (res < 0)
			ft_fprintf(2, "Error: Could not access the termcap data base.\n");
		else if (res == 0)
			ft_fprintf(2, "Error: Terminal type `%s' is not defined.\n",
				tty);
		exit(0);
	}
}

void		start_termios(t_sh *shell)
{
	char	*p;

	if (!(p = getenv("TERM")))
	{
		ft_fprintf(2, "Error: Specify a terminal type with ");
		ft_fprintf(2, "`setenv TERM <yourtype>`.\n");
		exit(1);
	}
	getentry(p);
	tcgetattr(STDIN_FILENO, &shell->term_backup);
	tcgetattr(STDIN_FILENO, &shell->term);
	shell->term.c_lflag &= ~ECHO & ~ICANON & ~ISIG;
	shell->term.c_cc[VMIN] = 1;
	shell->term.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &shell->term);
	termcap_do("ti");
}

void		controlled_termios(t_sh *shell)
{
	tcsetattr(STDIN_FILENO, TCSADRAIN, &shell->term);
}

void		reset_termios(t_sh *shell)
{
	tcsetattr(STDIN_FILENO, TCSADRAIN, &shell->term_backup);
}
