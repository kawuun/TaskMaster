/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvdovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 12:13:42 by dvdovenk          #+#    #+#             */
/*   Updated: 2017/11/13 12:13:43 by dvdovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_lib.h"

static int	parse_signal_3(char *line)
{
	if (ft_strequ(line, "USR2"))
		return (17);
	else if (ft_strequ(line, "POLL"))
		return (22);
	else if (ft_strequ(line, "PROF"))
		return (29);
	else if (ft_strequ(line, "SYS"))
		return (12);
	else if (ft_strequ(line, "TRAP"))
		return (5);
	else if (ft_strequ(line, "URG"))
		return (21);
	else if (ft_strequ(line, "VTALRM"))
		return (28);
	else if (ft_strequ(line, "XCPU"))
		return (30);
	else if (ft_strequ(line, "XFSZ"))
		return (31);
	else
		config_error();
	return (-1);
}

static int	parse_signal_2(char *line)
{
	if (ft_strequ(line, "PIPE"))
		return (13);
	else if (ft_strequ(line, "QUIT"))
		return (3);
	else if (ft_strequ(line, "SEGV"))
		return (11);
	else if (ft_strequ(line, "STOP"))
		return (23);
	else if (ft_strequ(line, "TERM"))
		return (15);
	else if (ft_strequ(line, "TSTP"))
		return (20);
	else if (ft_strequ(line, "TTIN"))
		return (26);
	else if (ft_strequ(line, "TTOU"))
		return (27);
	else if (ft_strequ(line, "USR1"))
		return (16);
	else
		return (parse_signal_3(line));
}

static int	parse_signal(char *line)
{
	if (ft_strequ(line, "ABRT"))
		return (6);
	else if (ft_strequ(line, "ALRM"))
		return (14);
	else if (ft_strequ(line, "BUS"))
		return (10);
	else if (ft_strequ(line, "CHLD"))
		return (18);
	else if (ft_strequ(line, "CONT"))
		return (25);
	else if (ft_strequ(line, "FPE"))
		return (8);
	else if (ft_strequ(line, "HUP"))
		return (1);
	else if (ft_strequ(line, "ILL"))
		return (4);
	else if (ft_strequ(line, "INT"))
		return (2);
	else if (ft_strequ(line, "KILL"))
		return (9);
	else
		return (parse_signal_2(line));
	return (0);
}

int			take_signal(char *line)
{
	if (!line)
		config_error();
	if (!ft_strnequ(line, "stopsignal: ", 12))
		config_error();
	line += 12;
	return (parse_signal(line));
}

int			take_autorestart(char *line)
{
	if (!line)
		config_error();
	if (!ft_strnequ(line, "autorestart: ", 13))
		config_error();
	line += 13;
	if (ft_strequ(line, "always"))
		return (1);
	else if (ft_strequ(line, "never"))
		return (0);
	else if (ft_strequ(line, "unexpected"))
		return (2);
	else
		config_error();
	return (-1);
}
