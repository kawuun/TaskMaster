/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skavunen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 15:35:47 by skavunen          #+#    #+#             */
/*   Updated: 2017/11/20 15:35:47 by skavunen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_lib.h"

void	control_timing(t_jobs *job)
{
	time_t	tocheck;
	char	*tmp;

	tocheck = (job->proc->start == STARTING ? job->proc->stime :
											job->proc->stopt);
	if (check_time(tocheck, (job->proc->start == STARTING ? job->starttime :
															job->stoptime)))
	{
		if (job->proc->start == WAITTOKILL)
			kill_it(job);
		else
		{
			job->proc->start = RUNNING;
			tmp = ft_strjoin(job->name, " has successfully started.\n");
			write_log(tmp, 0);
			ft_strdel(&tmp);
		}
	}
}

char	*reload(void)
{
	reload_config(NULL, NULL, NULL);
	return (ft_strdup("Config file was reloaded. Check your <logfile>."));
}

char	*help(char *(*f)(const char*, const char*))
{
	char	*tmp;
	char	*tmp2;

	tmp = "###########\nThanks for using our taskmaster!\n###########\n";
	tmp2 = f(tmp, "Here is all availiable commands:\n");
	tmp = f(tmp2, "status (<...>): status of all or selected processes.\n");
	ft_strdel(&tmp2);
	tmp2 = f(tmp, "stop <...>: stops selected processes.\n");
	ft_strdel(&tmp);
	tmp = f(tmp2, "start <...>: starts selected WAITING/KILLED processes.\n");
	ft_strdel(&tmp2);
	tmp2 = f(tmp, "continue <...>: continue work STOPPED processes.\n");
	ft_strdel(&tmp);
	tmp = f(tmp2, "restart <...>: restarts selected processes.\n");
	ft_strdel(&tmp2);
	tmp2 = f(tmp, "kill <...>: kill selected processes.\n");
	ft_strdel(&tmp);
	tmp = f(tmp2, "reload: reloads config file.\n");
	ft_strdel(&tmp2);
	tmp2 = f(tmp, "config: shows where is config file.");
	ft_strdel(&tmp);
	return (tmp2);
}

void	handler(int sig)
{
	int	i;

	if (sig == SIGHUP)
	{
		i = -1;
		while (++i < 3)
			if (g_serv->client_sock[i] != 0)
			{
				write_log(" #  ", 0);
				ft_fprintf(g_fd, "Client disconnected: Socket %d\n", \
				g_serv->client_sock[i]);
				close(g_serv->client_sock[i]);
				g_serv->client_sock[i] = 0;
			}
		reload_config(NULL, NULL, NULL);
	}
}
