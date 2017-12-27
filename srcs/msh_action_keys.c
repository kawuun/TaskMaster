/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_action_keys.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvdovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/22 21:23:34 by dvdovenk          #+#    #+#             */
/*   Updated: 2017/07/22 21:23:36 by dvdovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_lib.h"

int		paste_str(t_read *read)
{
	int		len;

	if (read->cpy[0])
	{
		len = ft_strlen(read->cpy);
		ft_memmove(read->cmd + read->pos + len, read->cmd + read->pos,
			ft_strlen(read->cmd + read->pos) + 1);
		ft_memcpy(read->cmd + read->pos, read->cpy, len);
		read->remember_insert = read->pos + len;
		termcap_home(read);
		termcap_do("cd");
		print(read);
		termcap_home(read);
		read->pos = read->remember_insert;
		place_cursor(read);
	}
	return (1);
}

int		cut_line_right(t_read *read)
{
	int		len;

	if ((len = ft_strlen(read->cmd + read->pos)) != 0)
	{
		ft_bzero(read->cpy, 1024);
		ft_memcpy(read->cpy, read->cmd + read->pos, len);
		ft_bzero(read->cmd + read->pos, len + 1);
		termcap_home(read);
		termcap_do("cd");
		print(read);
	}
	return (1);
}

int		cut_line_left(t_read *read)
{
	if (read->pos > 0)
	{
		ft_bzero(read->cpy, 1024);
		ft_memcpy(read->cpy, read->cmd, read->pos);
		ft_bzero(read->cmd, read->pos);
		ft_memmove(read->cmd, read->cmd + read->pos,
			ft_strlen(read->cmd + read->pos) + 1);
		print(read);
		termcap_home(read);
	}
	return (1);
}

int		cursor_left_word(t_read *read)
{
	while (read->cmd[read->pos] == ' ')
		term_go_backward(read);
	while (read->pos > 0 && read->cmd[read->pos] != ' ')
		term_go_backward(read);
	return (1);
}

int		cursor_right_word(t_read *read)
{
	while (read->cmd[read->pos] == ' ')
		term_go_forward(read);
	while (read->cmd[read->pos] && read->cmd[read->pos] != ' ')
		term_go_forward(read);
	return (1);
}
