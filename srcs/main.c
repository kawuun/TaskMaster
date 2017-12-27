/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skavunen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/17 16:27:02 by skavunen          #+#    #+#             */
/*   Updated: 2017/10/27 12:24:07 by skavunen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_lib.h"

void		config_error(void)
{
	ft_putstr_fd("taskmaster: Config File Syntax Error\n", g_fd);
	exit(0);
}

static int	make_server(int port, t_serv *serv)
{
	int	opt;

	opt = 1;
	serv->socket_desc = socket(AF_INET, SOCK_STREAM, 0);
	if (serv->socket_desc == -1 &&
		ft_printf("Could not create socket. Exiting...\n"))
		exit(EXIT_FAILURE);
	ft_printf("Socket created.\n");
	if (setsockopt(serv->socket_desc, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, \
		sizeof(opt)) && ft_printf("taskmaster: setsockopt failure...\n"))
		exit(EXIT_FAILURE);
	serv->server.sin_family = AF_INET;
	serv->server.sin_addr.s_addr = INADDR_ANY;
	serv->server.sin_port = htons(port);
	if (bind(serv->socket_desc, (struct sockaddr *)&serv->server,
		sizeof(serv->server)) < 0 && ft_printf("Bind failed. Exiting...\n"))
		exit(EXIT_FAILURE);
	ft_printf("Bind done.\n");
	listen(serv->socket_desc, 3);
	serv->c = sizeof(struct sockaddr_in);
	ft_printf("Waiting for incoming connections...\n");
	return (1);
}

static void	take_log(char *logfile)
{
	int	fd;

	fd = open(logfile, O_CREAT | O_WRONLY | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
	if (fd < 0)
	{
		ft_printf("Unable access logfile. Exiting...\n");
		exit(EXIT_FAILURE);
	}
	g_fd = fd;
}

int			main(int ac, char **av, char **env)
{
	t_jobs	*job;
	t_serv	*serv;

	if (ac != 4 &&
		ft_printf("Usage: ./server <port> <logfile> <config_file>\n"))
		return (1);
	serv = (t_serv*)ft_memalloc(sizeof(t_serv));
	ft_bzero(serv->client_message, 1024);
	make_server(ft_atoi(av[1]), serv);
	take_log(av[2]);
	g_config = av[3];
	signal(SIGHUP, handler);
	if ((job = load_jobs(env)))
	{
		g_jobs = job;
		load_programs(g_jobs);
		g_serv = serv;
		g_serv->max_sd = g_serv->socket_desc;
		monitoring(0, 0);
	}
	return (0);
}
