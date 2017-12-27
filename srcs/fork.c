/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skavunen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 14:04:11 by skavunen          #+#    #+#             */
/*   Updated: 2017/10/27 13:28:04 by skavunen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_lib.h"

void			launch_exe(t_jobs *job)
{
	int			ret;

	ret = 0;
	ret = execve(job->argv[0], job->argv, job->env);
	if (ret == -1)
		ft_putstr_fd("EXECVE FAILED!\n", g_fd);
}

void			fork_it(t_jobs *job)
{
	pid_t		launch;

	launch = fork();
	if (launch == 0)
	{
		set_settings(job);
		launch_exe(job);
	}
	else
	{
		job->proc->pid = launch;
		job->proc->stime = time(NULL);
		job->proc->start = STARTING;
		write_log(job->name, job->proc->start);
	}
}
