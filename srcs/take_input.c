/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvdovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/07 16:10:29 by dvdovenk          #+#    #+#             */
/*   Updated: 2017/05/07 16:10:30 by dvdovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_lib.h"

void	get_line_again(t_read *read)
{
	ft_bzero(read->cmd, 1024);
	read->his_pos = 0;
	termcap_do("do");
	termcap_goto("ch", 0, 0);
	termcap_do("cd");
	get_line(read);
}

void	insert_char(t_read *read, char key)
{
	ft_memmove((read->cmd + read->pos + 1), (read->cmd + read->pos),
		ft_strlen((read->cmd + read->pos)) + 1);
	read->size++;
	read->cmd[read->pos] = key;
	read->remember_insert = read->pos + 1;
	print(read);
	termcap_home(read);
	read->pos = read->remember_insert;
	place_cursor(read);
}

int		processing_key(t_read *read)
{
	int		status;

	if (read->key[0] == '\e')
		status = actions_extended(read);
	else
		status = actions_regular(read);
	return (status);
}

void	get_line(t_read *read)
{
	read->pos = 0;
	read->size = 0;
	ft_printf("{#bold}{#yellow}%s {#green}/~> {#eoc}", read->prompt);
	while (42)
	{
		read->key[0] = ft_getchar();
		if (processing_key(read) == 0)
			break ;
	}
	if (read->cmd[0] == '\0' || !check_correct(read))
		get_line_again(read);
	else if (read->cmd[0] != 'E' && read->cmd[1] != 'O' &&
		read->cmd[2] != 'F' && read->cmd[3] != '\0')
		termcap_end(read);
}

void	read_input(t_sh *shell)
{
	shell->read = read_init(shell->history, shell->prompt);
	controlled_termios(shell);
	get_line(shell->read);
	reset_termios(shell);
	if (ft_strcmp(shell->read->cmd, "EOF") == 0)
	{
		ft_printf("shutdown");
		shell->input = ft_strdup("shutdown");
	}
	else
		shell->input = ft_strdup(shell->read->cmd);
	update_history(shell);
	delete_read(shell->read);
	free(shell->read);
	write(1, "\n", 1);
}
