/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_toolkit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvdovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/29 16:18:44 by dvdovenk          #+#    #+#             */
/*   Updated: 2017/09/29 16:19:54 by dvdovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_lib.h"

void	make_intro(void)
{
	ft_fprintf(1, "$$$$$   $$  $$  $$$$$    $$$$   $");
	ft_fprintf(1, "$  $$  $$$$$   $$  $$  $$  $$\n");
	ft_fprintf(1, "$$  $$  $$  $$  $$  $$  $$  $$  $$");
	ft_fprintf(1, "  $$  $$      $$$ $$  $$ $$\n");
	ft_fprintf(1, "$$  $$  $$  $$  $$  $$  $$  $$  $$  $$");
	ft_fprintf(1, "  $$$$    $$ $$$  $$$$\n");
	ft_fprintf(1, "$$  $$   $$$$   $$  $$  $$  $$   ");
	ft_fprintf(1, "$$$$   $$      $$  $$  $$ $$\n");
	ft_fprintf(1, "$$$$$     $$    $$$$$    $$$$     $$");
	ft_fprintf(1, "    $$$$$   $$  $$  $$  $$\n\n");
}

int		check_correct(t_read *r)
{
	int		i;

	i = 0;
	while (r->cmd[i])
	{
		if (r->cmd[i] != ' ')
			return (1);
		i++;
	}
	return (0);
}

char	ft_getchar(void)
{
	unsigned char	buf;
	ssize_t			len;

	len = read(0, &buf, 1);
	if (!len)
		return (0);
	else
		return (buf);
}
