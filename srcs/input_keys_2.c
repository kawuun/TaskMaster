/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_keys_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvdovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/29 16:17:28 by dvdovenk          #+#    #+#             */
/*   Updated: 2017/09/29 16:17:28 by dvdovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_lib.h"

int		insert_enter(t_read *read)
{
	int		garbage;

	garbage = read->pos;
	return (0);
}

int		cursor_up_key(t_read *read)
{
	if (read->pos + read->cursor_start <= read->width)
		termcap_home(read);
	else
	{
		termcap_do("up");
		read->pos -= read->width;
	}
	return (1);
}

int		cursor_down_key(t_read *read)
{
	if (read->pos + read->width >= read->size)
		termcap_end(read);
	else
	{
		termcap_do("do");
		read->pos += read->width;
	}
	return (1);
}
