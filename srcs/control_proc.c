/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_proc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skavunen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 16:15:50 by skavunen          #+#    #+#             */
/*   Updated: 2017/10/27 12:26:59 by skavunen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_lib.h"

int		check_time(time_t time_h, int sec)
{
	if (time(NULL) - time_h >= sec)
		return (1);
	return (0);
}

char	*stop_proc(char **argv)
{
	char	*ret;
	int		i;
	t_jobs	*mj;

	i = 0;
	if (!argv[1])
		return (ft_strdup("usage: stop <processes>"));
	ret = ft_strnew(0);
	while (argv[++i])
	{
		mj = g_jobs;
		while (mj)
		{
			if (!ft_strcmp(argv[i], mj->name) && mj->proc->start != WAITING)
			{
				kill(mj->proc->pid, SIGTSTP);
				mj->proc->start = STOPPED;
				write_log(mj->name, mj->proc->start);
				set_status(&ret, mj);
				break ;
			}
			mj = mj->next;
		}
	}
	return (ft_strlen(ret) == 0 ? ft_strdup("No such proc.") : ret);
}

void	send_continue(t_jobs *job)
{
	int		status;

	status = 0;
	if (job->proc->start == STOPPED)
	{
		kill(job->proc->pid, SIGCONT);
		waitpid(job->proc->pid, &status, WNOHANG);
		if (check_time(job->proc->stime, job->starttime))
			job->proc->start = RUNNING;
		else
			job->proc->start = STARTING;
		write_log(job->name, job->proc->start);
	}
}

char	*continue_proc(char **argv)
{
	char	*ret;
	int		i;
	t_jobs	*movej;

	i = 0;
	if (!argv[1])
		return (ft_strdup("usage: continue <processes>"));
	ret = ft_strnew(0);
	while (argv[++i])
	{
		movej = g_jobs;
		while (movej)
		{
			if (!ft_strcmp(argv[i], movej->name) &&
				movej->proc->start != WAITING)
			{
				send_continue(movej);
				set_status(&ret, movej);
				break ;
			}
			movej = movej->next;
		}
	}
	return (ft_strlen(ret) == 0 ? ft_strdup("No such proc.") : ret);
}
