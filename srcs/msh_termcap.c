/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_termcap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvdovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/22 21:23:34 by dvdovenk          #+#    #+#             */
/*   Updated: 2017/07/22 21:23:36 by dvdovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_lib.h"

int		termcap_putchar(int c)
{
	write(2, &c, 1);
	return (0);
}

int		termcap_do(char *key)
{
	char	*tmp;

	if ((tmp = tgetstr(key, NULL)) == NULL)
		return (1);
	tputs(tmp, 0, termcap_putchar);
	return (0);
}

int		termcap_goto(char *key, int col, int row)
{
	char	*tmp;

	if ((tmp = tgetstr(key, NULL)) == NULL)
		return (1);
	tmp = tgoto(tmp, col, row);
	tputs(tmp, 0, termcap_putchar);
	return (0);
}

int		termcap_end(t_read *read)
{
	while (read->cmd[read->pos])
		term_go_forward(read);
	return (1);
}

void	place_cursor(t_read *read)
{
	termcap_goto("ch", 0, (read->pos + read->cursor_start) % read->width);
	read->linez = (read->pos + read->cursor_start) / read->width;
	if (read->linez != 0)
		termcap_goto("DO", read->linez, read->linez);
}
