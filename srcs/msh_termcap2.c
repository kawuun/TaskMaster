/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_termcap2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvdovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/29 16:20:41 by dvdovenk          #+#    #+#             */
/*   Updated: 2017/09/29 16:20:41 by dvdovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_lib.h"

int		termcap_home(t_read *r)
{
	r->linez = (r->pos + r->cursor_start) / r->width;
	termcap_goto("ch", 0, r->cursor_start);
	if (r->linez != 0)
		termcap_goto("UP", r->linez, r->linez);
	r->pos = 0;
	return (1);
}

void	print_str(t_read *read)
{
	while (read->cmd[read->pos])
	{
		if (read->cmd[read->pos] == '\n')
		{
			termcap_do("do");
			termcap_do("cr");
		}
		else
			ft_putchar(read->cmd[read->pos]);
		if (read->width != 0 && read->pos != 0 &&
			(read->pos + 1 + read->cursor_start) % (read->width) == 0)
		{
			termcap_do("do");
			termcap_do("cr");
		}
		read->pos++;
	}
}

void	print(t_read *read)
{
	termcap_home(read);
	termcap_do("cd");
	print_str(read);
}

int		term_go_backward(t_read *r)
{
	if (r->width != 0 && ((r->pos + r->cursor_start) % r->width) == 0)
	{
		termcap_do("up");
		termcap_goto("ch", 0, r->width - 1);
	}
	else
		termcap_do("le");
	r->pos--;
	return (1);
}

int		term_go_forward(t_read *r)
{
	r->pos++;
	if (r->width != 0 && ((r->pos + r->cursor_start) % r->width) == 0)
	{
		termcap_do("do");
		termcap_goto("ch", 0, 0);
	}
	else
		termcap_do("nd");
	return (1);
}
