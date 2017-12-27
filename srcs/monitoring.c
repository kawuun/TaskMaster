/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skavunen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/19 16:43:11 by skavunen          #+#    #+#             */
/*   Updated: 2017/10/27 14:10:23 by skavunen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_lib.h"

static char	*parse_msg(char *message)
{
	char	**argv;
	char	*resp;

	argv = make_argv(message);
	if (ft_strequ(message, "shutdown"))
		resp = message;
	else
		resp = make_response(argv);
	if (argv)
		ft_strdel_array(argv);
	return (resp);
}

static void	add_user(t_serv *serv, int i)
{
	if (FD_ISSET(serv->socket_desc, &serv->readfds))
	{
		if ((serv->new_socket = accept(serv->socket_desc,
			(struct sockaddr *)&serv->server, (socklen_t*)&serv->addrlen)) < 0)
		{
			perror("accept");
			exit(EXIT_FAILURE);
		}
		write_log("<!> ", 0);
		ft_fprintf(g_fd, "New Client: Socket %d | IP %s | Port %d\n", \
			serv->new_socket, inet_ntoa(serv->server.sin_addr), \
			ntohs(serv->server.sin_port));
		while (++i < 3)
		{
			if (serv->client_sock[i] == 0)
			{
				serv->client_sock[i] = serv->new_socket;
				write_log("<!> ", 0);
				ft_fprintf(g_fd, "Client socket ID: %d\n", i);
				break ;
			}
		}
	}
}

static void	operations_socket(t_serv *s, int i, char *message)
{
	while (++i < 3)
	{
		s->sd = s->client_sock[i];
		if (FD_ISSET(s->sd, &s->readfds))
		{
			if ((s->valread = read(s->sd, s->client_message, 1024)) == 0)
			{
				write_log("<!> ", 0);
				ft_fprintf(g_fd, "Client disconnected: Socket %d | IP %s\n", \
					s->sd, inet_ntoa(s->server.sin_addr));
				close(s->sd);
				s->client_sock[i] = 0;
			}
			else
			{
				message = parse_msg(s->client_message);
				send(s->sd, message, ft_strlen(message), 0);
				if (ft_strequ(message, "shutdown"))
					exit_taskmaster();
				ft_bzero(s->client_message, ft_strlen(s->client_message) + 1);
				ft_strdel(&message);
			}
		}
	}
}

static void	activity(t_serv *serv, struct timeval tv)
{
	int	i;

	FD_ZERO(&serv->readfds);
	FD_SET(serv->socket_desc, &serv->readfds);
	serv->max_sd = serv->socket_desc;
	i = -1;
	while (++i < 3)
	{
		serv->sd = serv->client_sock[i];
		if (serv->sd > 0)
			FD_SET(serv->sd, &serv->readfds);
		if (serv->sd > serv->max_sd)
			serv->max_sd = serv->sd;
	}
	serv->activity = select(serv->max_sd + 1, &serv->readfds,
		NULL, NULL, &tv);
	if ((serv->activity < 0) && (errno != EINTR))
		ft_printf("select error");
}

void		monitoring(pid_t tmp, int status)
{
	struct timeval tv;

	tv.tv_sec = 0;
	tv.tv_usec = CLOCKS_PER_SEC / 10;
	while (1)
	{
		g_jobs = check_timing();
		tmp = waitpid(WAIT_ANY, &status, WNOHANG);
		if (tmp > 0)
		{
			change_stat(tmp, status, g_jobs);
			tmp = 0;
		}
		activity(g_serv, tv);
		add_user(g_serv, -1);
		operations_socket(g_serv, -1, NULL);
	}
}
