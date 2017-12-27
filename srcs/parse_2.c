/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvdovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 12:13:45 by dvdovenk          #+#    #+#             */
/*   Updated: 2017/11/13 12:13:47 by dvdovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_lib.h"

void			ft_lstpushback(t_list **lst, void *content, size_t size)
{
	t_list	*node;

	node = *lst;
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = ft_lstnew(content, size);
	}
	else
		*lst = ft_lstnew(content, size);
}

char			**ft_arrdup(char **s)
{
	int		i;
	char	**new;

	i = -1;
	while (s[++i])
		continue ;
	new = (char**)ft_memalloc(sizeof(char*) * (i + 1));
	i = -1;
	while (s[++i])
		new[i] = ft_strdup(s[i]);
	return (new);
}

static int		*ft_intdup(int *array)
{
	int	i;
	int	*new;

	i = 0;
	while (array[i] != -100)
		i++;
	new = (int*)ft_memalloc(sizeof(int) * (i + 1));
	i = -1;
	while (array[++i] != -100)
		new[i] = array[i];
	new[i] = -100;
	return (new);
}

static t_jobs	*dup_job(t_jobs *new, t_jobs *jobs, int z, char *name)
{
	char	*itoa;

	itoa = ft_itoa(z);
	new->name = ft_strjoin(name, itoa);
	ft_strdel(&itoa);
	new->cmd = ft_strdup(jobs->cmd);
	new->dup = 1;
	new->argv = ft_arrdup(jobs->argv);
	new->process = 1;
	new->umask = jobs->umask;
	new->workingdir = ft_strdup(jobs->workingdir);
	new->autostart = jobs->autostart;
	new->autorestart = jobs->autorestart;
	new->exitcode = ft_intdup(jobs->exitcode);
	new->startretries = jobs->startretries;
	new->starttime = jobs->starttime;
	new->stopsignal = jobs->stopsignal;
	new->stoptime = jobs->stoptime;
	new->stdoutput = ft_strdup(jobs->stdoutput);
	new->stderror = ft_strdup(jobs->stderror);
	new->env = ft_arrdup(jobs->env);
	return (new);
}

void			dup_process(t_jobs *jobs)
{
	int		i;
	int		z;
	char	*name;
	t_jobs	*save;
	t_jobs	*new;

	i = jobs->process;
	z = 1;
	name = jobs->name;
	save = jobs;
	while (z != i)
	{
		if (!(new = (t_jobs*)ft_memalloc(sizeof(t_jobs))))
			exit(-1);
		new = dup_job(new, jobs, z, name);
		jobs->next = new;
		new->prev = jobs;
		jobs = jobs->next;
		z++;
	}
}
