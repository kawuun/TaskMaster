/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skavunen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/17 16:22:48 by skavunen          #+#    #+#             */
/*   Updated: 2017/10/27 13:58:31 by skavunen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_lib.h"

t_jobs		*take_params(t_jobs *program, char **map, int *pos, char **env)
{
	program->cmd = take_cmd(map[++(*pos)]);
	program->argv = make_argv(program->cmd);
	if ((program->process = take_num(map[++(*pos)], "numprocs: ", 10)) == 0)
		config_error();
	program->umask = take_num(map[++(*pos)], "umask: ", 7);
	program->workingdir = take_string(map[++(*pos)], "workingdir: ", 12);
	program->autostart = take_autostart(map[++(*pos)]);
	program->autorestart = take_autorestart(map[++(*pos)]);
	program->exitcode = take_exit(map[++(*pos)], "exitcodes: ", 10);
	program->startretries = take_num(map[++(*pos)], "startretries: ", 14);
	program->starttime = take_num(map[++(*pos)], "starttime: ", 11);
	program->stopsignal = take_signal(map[++(*pos)]);
	program->stoptime = take_num(map[++(*pos)], "stoptime: ", 10);
	program->stdoutput = take_string(map[++(*pos)], "stdout: ", 8);
	program->stderror = take_string(map[++(*pos)], "stderr: ", 8);
	program->env = take_env(env, map, pos);
	return (program);
}

t_jobs		*take_one_program(char **env, char **map, int *pos)
{
	t_jobs	*jobs;
	int		size;

	if (!(jobs = (t_jobs*)ft_memalloc(sizeof(t_jobs))))
		exit(0);
	size = ft_strlen(map[(*pos)]);
	if (map[(*pos)][size - 1] != ':')
		config_error();
	map[(*pos)][size - 1] = '\0';
	jobs->name = ft_strdup(map[(*pos)]);
	jobs = take_params(jobs, map, pos, env);
	if (jobs->process > 1)
		dup_process(jobs);
	return (jobs);
}

static void	ft_nodepushback(t_jobs **lst, char **map, int *pos, char **env)
{
	t_jobs	*node;

	node = *lst;
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = take_one_program(env, map, pos);
		node->next->prev = node;
	}
	else
		*lst = take_one_program(env, map, pos);
}

t_jobs		*parse_config(int fd, char **env, t_jobs *jobs)
{
	char	**config;
	int		i;

	config = take_file(fd);
	i = 0;
	if (!config[i] ||
		ft_strcmp("programs:", config[i]) != 0)
		config_error();
	i++;
	if (!config[i])
		config_error();
	ft_nodepushback(&jobs, config, &i, env);
	while (1)
	{
		if (!config[i])
			break ;
		ft_nodepushback(&jobs, config, &i, env);
	}
	ft_strdel_array(config);
	return (jobs);
}

t_jobs		*load_jobs(char **env)
{
	int		fd;
	t_jobs	*jobs;

	fd = open(g_config, O_RDONLY);
	if (fd < 0)
	{
		if (access(g_config, R_OK) == -1)
			ft_putstr_fd("taskmaster: Permission Denied To Config File\n",
					g_fd);
		else
			ft_putstr_fd("taskmaster: No Config File\n", g_fd);
		return (NULL);
	}
	jobs = parse_config(fd, env, NULL);
	close(fd);
	return (jobs);
}
