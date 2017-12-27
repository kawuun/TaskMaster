/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skavunen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 14:08:25 by skavunen          #+#    #+#             */
/*   Updated: 2017/10/24 14:12:23 by skavunen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_lib.h"

void	set_settings(t_jobs *job)
{
	umask(job->umask);
	chdir(job->workingdir);
	freopen(job->stdoutput, "w", stdout);
	freopen(job->stderror, "w", stderr);
}

void	ft_delete_list(t_list *lst)
{
	t_list	*next;

	while (lst)
	{
		next = lst->next;
		ft_memdel((void*)&lst->content);
		ft_memdel((void*)&lst);
		lst = next;
	}
}

void	delete_job(t_jobs *job)
{
	free(job->exitcode);
	ft_strdel(&job->name);
	ft_strdel(&job->cmd);
	ft_strdel(&job->workingdir);
	ft_strdel(&job->stdoutput);
	ft_strdel(&job->stderror);
	ft_strdel_array(job->argv);
	ft_strdel_array(job->env);
}
