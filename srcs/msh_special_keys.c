/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_special_keys.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvdovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/22 21:23:34 by dvdovenk          #+#    #+#             */
/*   Updated: 2017/07/22 21:23:36 by dvdovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_lib.h"

int		history_up(t_read *read)
{
	if (read->his && read->his[read->his_pos + 1])
	{
		read->his_pos++;
		read->cmd = read->his[read->his_pos];
		print(read);
		read->size = read->pos + 1;
	}
	return (1);
}

int		history_down(t_read *read)
{
	if (read->his && read->his_pos > 0 && read->his[read->his_pos - 1])
	{
		read->his_pos--;
		read->cmd = read->his[read->his_pos];
		print(read);
		read->size = read->pos + 1;
	}
	return (1);
}

int		reset_line(t_read *read)
{
	termcap_end(read);
	ft_bzero(read->cmd, 1024);
	termcap_do("do");
	termcap_do("cr");
	ft_printf("{#bold}{#yellow}%s {#green}/~> {#eoc}", read->prompt);
	read->his_pos = 0;
	read->pos = 0;
	read->size = 0;
	return (1);
}

int		end_reading(t_read *read)
{
	if (read->cmd[0])
		return (1);
	ft_bzero(read->cmd, 1024);
	ft_memcpy(read->cmd, "EOF", 3);
	return (0);
}
