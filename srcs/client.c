/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvdovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/29 19:01:17 by dvdovenk          #+#    #+#             */
/*   Updated: 2017/04/29 19:01:20 by dvdovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_lib.h"

static t_sh	*ft_shell_init(void)
{
	t_sh	*sh;

	if (!(sh = (t_sh*)ft_memalloc(sizeof(t_sh))))
		return (NULL);
	sh->prompt = "Enter message";
	sh->history = (char**)ft_memalloc(sizeof(char*) * (HISTORY_COUNT + 1));
	return (sh);
}

static void	loop(t_sh *shell, int sock)
{
	int		status;
	char	server_reply[2000];

	status = 1;
	ft_bzero(server_reply, 2000);
	while (status)
	{
		read_input(shell);
		if (ft_strequ(shell->input, "exit"))
			return ;
		if (send(sock, shell->input, ft_strlen(shell->input), 0) < 0 &&
			ft_fprintf(2, "Send failed. Exiting...\n"))
			return ;
		if (ft_strequ(shell->input, "shutdown"))
			break ;
		if (recv(sock, server_reply, 2000, 0) < 0 &&
			ft_fprintf(2, "Recv failed. Exiting...\n"))
			break ;
		ft_printf("%s\n", server_reply);
		ft_bzero(server_reply, ft_strlen(server_reply) + 1);
		ft_strdel(&shell->input);
	}
	ft_strdel(&shell->input);
}

static void	ft_clear_shell(t_sh *shell)
{
	if (shell->history)
		ft_strdel_array(shell->history);
	free(shell);
}

static int	connect_to_server(int port)
{
	int					sock;
	struct sockaddr_in	server;

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1)
	{
		ft_printf("Could not create socket\n");
		return (-1);
	}
	ft_printf("Socket created\n");
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0)
	{
		ft_fprintf(2, "Connection failed. Exiting...\n");
		return (-1);
	}
	ft_fprintf(2, "Connected\n");
	return (sock);
}

int			main(int argc, char **argv)
{
	t_sh	*shell;
	int		sock;

	if (argc != 2 && ft_fprintf(2, "Usage: ./client <server_port>\n"))
		return (1);
	if ((sock = connect_to_server(ft_atoi(argv[1]))) == -1)
		return (1);
	if ((shell = ft_shell_init()))
	{
		start_termios(shell);
		make_intro();
		loop(shell, sock);
		ft_clear_shell(shell);
		termcap_do("te");
	}
	close(sock);
	return (1);
}
