/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toolkit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvdovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 20:11:20 by dvdovenk          #+#    #+#             */
/*   Updated: 2017/11/15 19:13:49 by skavunen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_lib.h"

void	exit_taskmaster(void)
{
	t_jobs	*tmp;
	t_jobs	*delete;

	tmp = g_jobs;
	write_log("Clearing data.\n", 0);
	while (tmp)
	{
		if (tmp->proc && tmp->proc->start != WAITING &&
			tmp->proc->start != KILLED)
		{
			kill_it(tmp);
			free(tmp->proc);
		}
		delete = tmp->next;
		delete_job(tmp);
		free(tmp);
		tmp = delete;
	}
	write_log("Shutdown Server.\n", 0);
	exit(0);
}

char	**take_env(char **env, char **m, int *pos)
{
	int		i;
	char	**tmp_env;

	i = 0;
	(*pos)++;
	if (!m[(*pos)])
		return (ft_arrdup(env));
	if (ft_strncmp("env:", m[(*pos)], 4) != 0)
		return (ft_arrdup(env));
	++(*pos);
	i = (*pos);
	while (m[i] && m[i][0] >= 65 && m[i][0] <= 90)
		i++;
	tmp_env = (char**)ft_memalloc(sizeof(char*) * (i + 1));
	i = 0;
	while (m[(*pos)] && m[(*pos)][0] >= 65 && m[(*pos)][0] <= 90)
	{
		tmp_env[i] = ft_strdup(m[(*pos)]);
		i++;
		(*pos)++;
	}
	tmp_env[i] = NULL;
	return (tmp_env);
}

char	**take_file(int fd)
{
	t_list	*lst;
	t_list	*save;
	char	*line;
	char	**config;
	int		i;

	i = 0;
	lst = NULL;
	while (get_next_line(fd, &line))
	{
		ft_lstpushback(&lst, line, ft_strlen(line) + 1);
		ft_strdel(&line);
		i++;
	}
	config = (char**)ft_memalloc(sizeof(char*) * (i + 1));
	i = -1;
	save = lst;
	while (lst)
	{
		config[++i] = ft_strtrim(lst->content);
		lst = lst->next;
	}
	config[++i] = NULL;
	ft_delete_list(save);
	return (config);
}

void	change_stat(int tmp, int status, t_jobs *job)
{
	while (job)
	{
		if (job->proc->pid == tmp && job->proc->start != KILLED)
		{
			control_proc(job, status);
			break ;
		}
		job = job->next;
	}
}

t_jobs	*check_timing(void)
{
	t_jobs	*tmp;

	tmp = g_jobs;
	while (tmp)
	{
		if (tmp->proc->start == WAITTOKILL || tmp->proc->start == STARTING)
		{
			control_timing(tmp);
		}
		tmp = tmp->next;
	}
	return (g_jobs);
}
