/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvdovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 12:13:53 by dvdovenk          #+#    #+#             */
/*   Updated: 2017/11/13 12:13:54 by dvdovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_lib.h"

int		take_autostart(char *line)
{
	if (!line)
		config_error();
	if (!ft_strnequ(line, "autostart: ", 11))
		config_error();
	line += 11;
	if (ft_strequ(line, "true"))
		return (1);
	else if (ft_strequ(line, "false"))
		return (0);
	else
		config_error();
	return (-1);
}

char	*take_string(char *line, char *param, int size)
{
	if (!line)
		config_error();
	if (!ft_strnequ(line, param, size))
		config_error();
	line += size;
	return (ft_strdup(line));
}

int		*get_array(char *line, int size)
{
	int	k;
	int	i;
	int	*array;

	line += size + 1;
	i = size + 1;
	k = 0;
	while (line[i])
	{
		if (line[i] == ',')
			k++;
		i++;
	}
	array = (int*)ft_memalloc(sizeof(int) * (k + 2));
	k = 0;
	while (*line)
	{
		array[k] = ft_atoi(line);
		k++;
		while (*(line + 1) && *line != ',')
			line++;
		line++;
	}
	array[k] = -100;
	return (array);
}

int		*take_exit(char *line, char *param, int size)
{
	if (!line)
		config_error();
	if (!ft_strnequ(line, param, size))
		config_error();
	return (get_array(line, size));
}

int		take_num(char *line, char *param, int size)
{
	if (!line)
		config_error();
	while (*line && (*line == ' ' || *line == '\t'))
		line++;
	if (!ft_strnequ(line, param, size))
		config_error();
	line += size;
	return (ft_atoi(line));
}
