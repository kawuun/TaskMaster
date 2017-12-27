/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvdovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 20:13:30 by dvdovenk          #+#    #+#             */
/*   Updated: 2017/10/27 20:13:31 by dvdovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_lib.h"

static int	compare_values(t_jobs *b, t_jobs *t)
{
	int	i;
	int	status;

	status = 1;
	if (!ft_strequ(b->name, t->name) || !ft_strequ(b->cmd, t->cmd) ||
		(b->process != t->process) || (b->umask != t->umask) ||
		!ft_strequ(b->workingdir, t->workingdir) ||
		b->autostart != t->autostart || b->autorestart != t->autorestart ||
		b->startretries != t->startretries || b->starttime != t->starttime ||
		b->stopsignal != t->stopsignal || b->stoptime != t->stoptime ||
		!ft_strequ(b->stdoutput, t->stdoutput) ||
		!ft_strequ(b->stderror, t->stderror))
		return (0);
	i = -1;
	while (b->env[++i] && t->env[i])
		if (!ft_strequ(b->env[i], t->env[i]))
			return (0);
	if (b->env[i] || t->env[i])
		return (0);
	i = -1;
	while (b->exitcode[++i] != -100)
		if (b->exitcode[i] != t->exitcode[i])
			return (0);
	return (status);
}

static void	destroy_unused(void)
{
	t_jobs	*begin;
	t_jobs	*tmp;

	begin = g_jobs;
	while (begin)
	{
		if (!begin->found)
		{
			if (begin->proc->start != KILLED && begin->proc->start != WAITING)
				kill_it(begin);
			free(begin->proc);
		}
		tmp = begin->next;
		delete_job(begin);
		free(begin);
		begin = tmp;
	}
}

static int	take_all(t_jobs **reloaded, t_jobs *old)
{
	while (old->next && old->next->dup &&
		(*reloaded)->next && (*reloaded)->next->dup)
	{
		(*reloaded)->proc = old->proc;
		old->found = 1;
		old = old->next;
		(*reloaded) = (*reloaded)->next;
	}
	(*reloaded)->proc = old->proc;
	old->found = 1;
	return (1);
}

static void	skip_dup(t_jobs **begin)
{
	while ((*begin)->next && (*begin)->next->dup)
		(*begin) = (*begin)->next;
}

void		reload_config(t_jobs *reload, t_jobs *begin, t_jobs *tmp)
{
	if ((reload = load_jobs(g_jobs->env)))
	{
		begin = reload;
		while (begin)
		{
			tmp = g_jobs;
			while (tmp)
			{
				if (compare_values(begin, tmp) && take_all(&begin, tmp))
					break ;
				skip_dup(&tmp);
				tmp = tmp->next;
			}
			skip_dup(&begin);
			begin = begin->next;
		}
		destroy_unused();
		load_programs(reload);
		g_jobs = reload;
		write_log("Reloading Config Was Successful.\n", 0);
	}
	else
		write_log("Reloading Config Error (!).\n", 0);
}
