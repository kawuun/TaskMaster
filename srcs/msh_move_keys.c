/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_move_keys.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvdovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/22 21:23:34 by dvdovenk          #+#    #+#             */
/*   Updated: 2017/07/22 21:23:36 by dvdovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_lib.h"

int		cursor_left_key(t_read *read)
{
	if (read->pos > 0)
		term_go_backward(read);
	return (1);
}

int		cursor_right_key(t_read *read)
{
	if (read->cmd[read->pos])
		term_go_forward(read);
	return (1);
}

int		delete_key(t_read *read)
{
	if (read->pos >= 0 && read->cmd[read->pos])
	{
		read->size--;
		ft_memmove((read->cmd + read->pos), (read->cmd + read->pos + 1),
		ft_strlen(read->cmd + read->pos + 1) + 1);
		read->remember_insert = read->pos;
		print(read);
		termcap_home(read);
		read->pos = read->remember_insert;
		place_cursor(read);
	}
	return (1);
}

int		backspace(t_read *read)
{
	if (read->pos > 0)
	{
		read->size--;
		ft_memmove((read->cmd + read->pos - 1), (read->cmd + read->pos),
		ft_strlen(read->cmd + read->pos) + 1);
		read->remember_insert = read->pos - 1;
		print(read);
		termcap_home(read);
		read->pos = read->remember_insert;
		place_cursor(read);
	}
	return (1);
}
