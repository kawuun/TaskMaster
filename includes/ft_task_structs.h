/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_task_structs.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvdovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 21:59:08 by dvdovenk          #+#    #+#             */
/*   Updated: 2017/10/27 13:46:31 by skavunen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TASK_STRUCTS_H
# define FT_TASK_STRUCTS_H

# include "ft_lib.h"

typedef	struct	s_read
{
	char	*cmd;
	int		linez;
	int		size;
	int		remember_insert;
	int		pos;
	int		height;
	int		width;
	char	key[1];
	char	key_extended[5];
	char	cpy[1024];
	int		cursor_start;
	int		his_pos;
	char	*prompt;
	char	**his;
}				t_read;

typedef struct	s_jobs
{
	char			*name;
	char			*cmd;
	char			**argv;
	int				dup;
	char			found;
	int				process;
	int				umask;
	char			*workingdir;
	int				autostart;
	int				autorestart;
	int				*exitcode;
	int				startretries;
	int				starttime;
	int				stopsignal;
	int				stoptime;
	char			*stdoutput;
	char			*stderror;
	char			**env;
	struct s_proc	*proc;
	struct s_jobs	*prev;
	struct s_jobs	*next;
}				t_jobs;

typedef struct	s_sh
{
	char			**history;
	char			*prompt;
	char			*input;
	struct s_read	*read;
	struct termios	term;
	struct termios	term_backup;
}				t_sh;

typedef struct	s_serv
{
	int					socket_desc;
	int					client_sock[3];
	int					c;
	int					read_size;
	int					max_sd;
	int					sd;
	int					activity;
	int					new_socket;
	int					addrlen;
	int					valread;
	fd_set				readfds;
	struct sockaddr_in	server;
	struct sockaddr_in	client;
	char				client_message[1024];
}				t_serv;

typedef struct	s_proc
{
	int				pid;
	int				start;
	time_t			stime;
	time_t			stopt;
}				t_proc;

typedef int		(*t_action) (t_read *read);

typedef struct	s_spec_keys
{
	t_action	function;
	int			value[5];
}				t_spec_keys;

#endif
