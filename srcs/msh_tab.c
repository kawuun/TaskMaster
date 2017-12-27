/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_tab.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvdovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 14:22:03 by dvdovenk          #+#    #+#             */
/*   Updated: 2017/12/07 14:22:03 by dvdovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_lib.h"

int		ft_first_cmd(char *line, int count)
{
	int	i;

	i = count;
	if (line[i] == ' ' && line[i - 1] != ' ')
		i--;
	while (i > 0 && line[i] != ' ')
		i--;
	while (i > 0 && line[i] == ' ')
		i--;
	if (i == 0 || line[i] == ';' || line[i] == '|')
		return (1);
	return (0);
}

char	*take_word(char *line, int count)
{
	int		i;
	char	*tmp;

	if (count == 0)
		return (NULL);
	i = count;
	if (i > 0 && line[i] == ' ' && line[i - 1] != ' ')
		i--;
	while (i > 0 && line[i] != ' ')
		i--;
	if (line[i] == ' ')
		i++;
	if (count == i)
		return (NULL);
	tmp = ft_strnew(count - i + 2);
	ft_memcpy(tmp, line + i, count - i);
	tmp[count - i] = '\0';
	return (tmp);
}

char	*ft_builtin(char *str)
{
	int		i;

	i = ft_strlen(str);
	if (ft_strncmp("status", str, i) == 0)
		return ("status");
	else if (ft_strncmp("exit", str, i) == 0)
		return ("exit");
	else if (ft_strncmp("kill", str, i) == 0)
		return ("kill");
	else if (ft_strncmp("restart", str, i) == 0)
		return ("restart");
	else if (ft_strncmp("stop", str, i) == 0)
		return ("stop");
	else if (ft_strncmp("start", str, i) == 0)
		return ("start");
	else if (ft_strncmp("shutdown", str, i) == 0)
		return ("shutdown");
	return (NULL);
}

void	complete_word(t_read *read, char *autocomp, char *tmp)
{
	int	size;
	int	i;
	int	j;

	i = ft_strlen(autocomp);
	j = ft_strlen(tmp);
	size = i - j;
	if (size == 0)
		return ;
	ft_memmove(read->cmd + read->pos + size, read->cmd + read->pos,
		ft_strlen(read->cmd + read->pos) + 1);
	ft_memcpy(read->cmd + read->pos, autocomp + j, size);
	read->remember_insert = read->pos + size;
	print(read);
	termcap_home(read);
	read->pos = read->remember_insert;
	place_cursor(read);
}

int		tab_complete(t_read *read)
{
	char	*tmp;
	char	*tmp2;

	tmp = take_word(read->cmd, read->pos);
	if (!tmp)
		return (1);
	else if (tmp[0] == '\0')
	{
		ft_strdel(&tmp);
		return (1);
	}
	else if (ft_first_cmd(read->cmd, read->pos) && (tmp2 = ft_builtin(tmp)))
		complete_word(read, tmp2, tmp);
	ft_strdel(&tmp);
	return (1);
}
