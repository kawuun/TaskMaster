/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   response.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skavunen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 14:47:34 by skavunen          #+#    #+#             */
/*   Updated: 2017/10/27 13:52:00 by skavunen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_lib.h"

static void	join_status(char **ret, t_jobs *job)
{
	char	*str;

	str = *ret;
	if (job->proc->start == STOPPED)
		str = ft_strjoin(str, ": \033[22;36mSTOPPED\e[0m");
	else if (job->proc->start == WAITING)
		str = ft_strjoin(str, ": \033[01;37mWAITING\e[0m");
	else if (job->proc->start == KILLED)
		str = ft_strjoin(str, ": \033[22;31mKILLED\e[0m");
	else if (job->proc->start == WAITTOKILL)
		str = ft_strjoin(str, ": \033[01;33mWAITING TO KILL\e[0m");
	else if (job->proc->start == RUNNING)
		str = ft_strjoin(str, ": \033[22;32mRUNNING\e[0m");
	else
		str = ft_strjoin(str, ": \033[22;36mSTARTING\e[0m");
	*ret = str;
}

void		set_status(char **ret, t_jobs *job)
{
	char	*tmp;
	char	*str;

	str = *ret;
	if (str[0])
	{
		tmp = str;
		str = ft_strjoin(str, "\n");
		ft_strdel(&tmp);
	}
	tmp = str;
	str = ft_strjoin(str, job->name);
	ft_strdel(&tmp);
	tmp = str;
	join_status(&str, job);
	ft_strdel(&tmp);
	*ret = str;
}

static char	*full_status(t_jobs *job)
{
	char	*ret;

	ret = ft_strnew(0);
	while (job)
	{
		set_status(&ret, job);
		job = job->next;
	}
	return (ret);
}

static char	*response_status(char **argv)
{
	int		i;
	t_jobs	*movej;
	char	*ret;

	i = 0;
	if (!argv[1])
		return (full_status(g_jobs));
	ret = ft_strnew(0);
	while (argv[++i])
	{
		movej = g_jobs;
		while (movej)
		{
			if (!ft_strcmp(argv[i], movej->name))
			{
				set_status(&ret, movej);
				break ;
			}
			movej = movej->next;
		}
	}
	return (ft_strlen(ret) == 0 ? ft_strdup("No such proc.") : ret);
}

char		*make_response(char **argv)
{
	if (!ft_strcmp(argv[0], "status"))
		return (response_status(argv));
	else if (!ft_strcmp(argv[0], "stop"))
		return (stop_proc(argv));
	else if (!ft_strcmp(argv[0], "continue"))
		return (continue_proc(argv));
	else if (!ft_strcmp(argv[0], "help"))
		return (help(&ft_strjoin));
	else if (!ft_strcmp(argv[0], "reload"))
		return (reload());
	else if (!ft_strcmp(argv[0], "config"))
		return (ft_strjoin("Config file is here: ", g_config));
	else if (!ft_strcmp(argv[0], "restart"))
		return (restart_proc(argv));
	else if (!ft_strcmp(argv[0], "kill"))
		return (kill_proc(argv));
	else if (!ft_strcmp(argv[0], "start"))
		return (start_proc(argv));
	return (ft_strdup("taskmaster: invalid command."));
}
