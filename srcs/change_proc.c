/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_proc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skavunen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 14:33:05 by skavunen          #+#    #+#             */
/*   Updated: 2017/11/15 20:23:25 by skavunen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_lib.h"

void	write_log(char *msg, int code)
{
	time_t		curtime;
	struct tm	*tinf;
	char		buf[80];

	time(&curtime);
	tinf = localtime(&curtime);
	strftime(buf, 80, "[%Y/%m/%e %X] ", tinf);
	ft_fprintf(g_fd, buf);
	ft_fprintf(g_fd, "%s", msg);
	if (code == 3)
		ft_fprintf(g_fd, " has stopped.\n");
	else if (code == 2)
		ft_fprintf(g_fd, " is running.\n");
	else if (code == 4)
		ft_fprintf(g_fd, " was killed.\n");
	else if (code == 5)
		ft_fprintf(g_fd, " is waiting to be killed.\n");
	else if (code != 0)
		ft_fprintf(g_fd, " is starting.\n");
}

char	*start_proc(char **argv)
{
	char	*ret;
	int		i;
	t_jobs	*mj;

	i = 0;
	if (!argv[1])
		return (ft_strdup("usage: start <processes>"));
	ret = ft_strnew(0);
	while (argv[++i])
	{
		mj = g_jobs;
		while (mj)
		{
			if (!ft_strcmp(argv[i], mj->name))
			{
				if (mj->proc->start != WAITING && mj->proc->start != KILLED)
					kill_it(mj);
				fork_it(mj);
				set_status(&ret, mj);
				break ;
			}
			mj = mj->next;
		}
	}
	return (ft_strlen(ret) == 0 ? ft_strdup("No such proc.") : ret);
}

int		exit_proc(t_jobs *job, int status, int i)
{
	if (job->proc->start == STARTING && --job->startretries > 0)
	{
		fork_it(job);
		return (1);
	}
	while (job->exitcode[i] != -100 && WEXITSTATUS(status) != job->exitcode[i])
		i++;
	if (job->exitcode[i] != -100 && WEXITSTATUS(status) == job->exitcode[i])
	{
		if (job->autorestart == 1)
			fork_it(job);
		else
		{
			job->proc->start = WAITTOKILL;
			write_log(job->name, WAITTOKILL);
			job->proc->stopt = time(NULL);
			return (-1);
		}
	}
	else if (job->autorestart == 2 && job->proc->start != STOPPED)
		fork_it(job);
	else if (job->proc->start != STOPPED)
		return (0);
	return (1);
}

int		signal_proc(t_jobs *job, int status)
{
	if (job->proc->start == STARTING && --job->startretries > 0)
	{
		fork_it(job);
		return (1);
	}
	else if (WTERMSIG(status) == job->stopsignal)
	{
		if (job->autorestart == 1)
			fork_it(job);
		else
		{
			job->proc->start = WAITTOKILL;
			write_log(job->name, WAITTOKILL);
			job->proc->stopt = time(NULL);
			return (-1);
		}
	}
	else if (job->autorestart == 2 && job->proc->start != STOPPED)
		fork_it(job);
	else if (job->proc->start != STOPPED)
		return (0);
	return (1);
}

void	control_proc(t_jobs *job, int status)
{
	if (WIFEXITED(status) && !exit_proc(job, status, 0))
	{
		job->proc->start = KILLED;
		write_log(job->name, job->proc->start);
	}
	else if (WIFSIGNALED(status) && !signal_proc(job, status))
	{
		job->proc->start = KILLED;
		write_log(job->name, job->proc->start);
	}
}
