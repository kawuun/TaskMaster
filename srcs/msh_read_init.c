/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_read_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvdovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/22 21:23:34 by dvdovenk          #+#    #+#             */
/*   Updated: 2017/07/22 21:23:36 by dvdovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_lib.h"

static char	**tmp_history(char **history, t_read *read)
{
	int		i;
	char	**new_his;

	new_his = NULL;
	if (history)
	{
		i = 0;
		new_his = (char**)ft_memalloc(sizeof(char*) * (HISTORY_COUNT + 1));
		while (++i < HISTORY_COUNT && history[i - 1])
			new_his[i] = ft_strcpy(ft_strnew(1024), history[i - 1]);
		*new_his = read->cmd;
	}
	return (new_his);
}

t_read		*read_init(char **his, char *prompt)
{
	t_read			*read;
	struct winsize	w;

	read = NULL;
	if (!(read = (t_read*)ft_memalloc(sizeof(t_read))))
		exit(3);
	ioctl(0, TIOCGWINSZ, &w);
	read->width = w.ws_col;
	read->height = w.ws_row;
	read->linez = 0;
	read->prompt = ft_strdup(prompt);
	read->cursor_start = ft_strlen(read->prompt) + 5;
	read->cmd = ft_strnew(1024);
	read->his = tmp_history(his, read);
	read->his_pos = 0;
	return (read);
}

void		update_history(t_sh *shell)
{
	int	i;

	i = HISTORY_COUNT;
	if (shell->history[0] &&
		!ft_strcmp(shell->history[0], shell->read->cmd))
		return ;
	if (shell->history[i - 1])
	{
		ft_strdel(&shell->history[i - 1]);
		shell->history[i - 1] = NULL;
	}
	while (--i)
		shell->history[i] = shell->history[i - 1];
	shell->history[0] = ft_strdup(shell->read->cmd);
}

void		delete_read(t_read *read)
{
	if (read->prompt)
		ft_strdel(&read->prompt);
	if (read->his)
		ft_strdel_array(read->his);
}
