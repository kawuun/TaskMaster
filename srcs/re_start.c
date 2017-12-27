/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_start.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skavunen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 17:24:28 by skavunen          #+#    #+#             */
/*   Updated: 2017/10/27 13:49:59 by skavunen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_lib.h"

void			restart_it(t_jobs *job)
{
	if (job->proc->start != WAITING)
		kill(job->proc->pid, SIGKILL);
	fork_it(job);
}

char			*restart_proc(char **argv)
{
	int		i;
	char	*ret;
	t_jobs	*movej;

	i = 0;
	if (!argv[1])
		return (ft_strdup("usage: restart <processes>"));
	ret = ft_strnew(0);
	while (argv[++i])
	{
		movej = g_jobs;
		while (movej)
		{
			if (!ft_strcmp(argv[i], movej->name))
			{
				restart_it(movej);
				set_status(&ret, movej);
				break ;
			}
			movej = movej->next;
		}
	}
	return (ft_strlen(ret) == 0 ? ft_strdup("No such proc.") : ret);
}

void			kill_it(t_jobs *job)
{
	if (job->proc->start != KILLED)
	{
		kill(job->proc->pid, SIGKILL);
		job->proc->start = KILLED;
		write_log(job->name, job->proc->start);
	}
}

char			*kill_proc(char **argv)
{
	int			i;
	char		*ret;
	t_jobs		*movej;

	i = 0;
	if (!argv[1])
		return (ft_strdup("usage: kill <processes>"));
	ret = ft_strnew(0);
	while (argv[++i])
	{
		movej = g_jobs;
		while (movej)
		{
			if (!ft_strcmp(argv[i], movej->name) &&
				movej->proc->start != WAITING)
			{
				kill_it(movej);
				set_status(&ret, movej);
				break ;
			}
			movej = movej->next;
		}
	}
	return (ft_strlen(ret) == 0 ? ft_strdup("No such proc.") : ret);
}
