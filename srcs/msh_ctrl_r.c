/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ctrl_r.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvdovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/22 21:23:34 by dvdovenk          #+#    #+#             */
/*   Updated: 2017/07/22 21:23:36 by dvdovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_lib.h"

static void	print_find_str(char *big, char *little, int i, int j)
{
	while (big[++i] != '\0')
	{
		j = 0;
		while (big[i + j] && big[i + j] == little[j])
			j++;
		if (little[j] == '\0')
		{
			termcap_do("so");
			termcap_do("us");
			ft_putstr(little);
			termcap_do("se");
			termcap_do("ue");
			i += j;
			break ;
		}
		if (big[i] == '\n')
		{
			termcap_do("do");
			termcap_do("cr");
		}
		else
			ft_putchar(big[i]);
	}
	if (big + i)
		ft_putstr(big + i);
}

static void	find_str(char *tmp, t_read *read)
{
	int		i;

	i = -1;
	while (read->his[++i])
		if (ft_strstr(read->his[i], tmp) != NULL)
			break ;
	if (read->his[i] == NULL)
	{
		termcap_do("cr");
		termcap_do("cd");
		ft_printf("failed history search > %s_", tmp);
	}
	else
	{
		termcap_do("cr");
		termcap_do("cd");
		ft_printf("history search > ");
		print_find_str(read->his[i], tmp, -1, 0);
		read->cmd = read->his[i];
		read->his_pos = i;
	}
}

static void	add_char(char tmp[], int *i, t_read *read, char buf)
{
	tmp[(*i)] = buf;
	find_str(tmp, read);
	(*i)++;
}

static void	delete_char(char tmp[], int *i, t_read *read)
{
	(*i)--;
	tmp[(*i)] = '\0';
	find_str(tmp, read);
}

int			history_search(t_read *r)
{
	char	tmp[1024];
	char	buf;
	int		i;

	termcap_end(r);
	termcap_do("do");
	termcap_do("cr");
	termcap_do("vi");
	ft_printf("history search > ");
	i = 0;
	ft_bzero(tmp, 1024);
	while ((buf = ft_getchar()))
	{
		if (buf == 127 && i > 0)
			delete_char(tmp, &i, r);
		else if (!ft_isprint(buf))
			break ;
		else
			add_char(tmp, &i, r, buf);
	}
	termcap_do("ve");
	termcap_do("up");
	termcap_goto("ch", 0, (r->pos + r->cursor_start) % r->width);
	print(r);
	return (1);
}
