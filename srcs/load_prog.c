/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_prog.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skavunen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/17 16:41:37 by skavunen          #+#    #+#             */
/*   Updated: 2017/10/24 14:43:55 by skavunen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_lib.h"

void	load_programs(t_jobs *job)
{
	int		i;

	while (job)
	{
		if (!job->proc)
		{
			job->proc = (t_proc*)ft_memalloc(sizeof(t_proc));
			if (job->autostart)
			{
				ft_fprintf(g_fd, "STARTING PROGRAM: %s\n", job->name);
				ft_putstr_fd("WITH ARGS: ", g_fd);
				i = -1;
				while (job->argv[++i])
					ft_fprintf(g_fd, "%s ", job->argv[i]);
				ft_fprintf(g_fd, "\n");
				fork_it(job);
				ft_fprintf(g_fd, "PROGRAM HAS STARTED...\n");
				ft_fprintf(g_fd, "<====================>\n");
			}
			else
				job->proc->start = WAITING;
		}
		job = job->next;
	}
}
