/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lib.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvdovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 18:32:06 by dvdovenk          #+#    #+#             */
/*   Updated: 2017/10/27 13:44:51 by skavunen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LIB_H
# define FT_LIB_H

# include <sys/wait.h>
# include <signal.h>
# include <term.h>
# include <termios.h>
# include <stdio.h>
# include <sys/types.h>
# include <errno.h>
# include <netinet/in.h>
# include <sys/stat.h>
# include <sys/socket.h>
# include <arpa/inet.h>
# include <dirent.h>
# include <fcntl.h>
# include <time.h>
# include "ft_task_structs.h"
# include "../libft/includes/libft.h"

# define WAITING -3
# define STOPPED 3
# define RUNNING 2
# define STARTING 1
# define KILLED 4
# define WAITTOKILL 5
# define HISTORY_COUNT 20

int		g_fd;
char	*g_config;
t_jobs	*g_jobs;
t_serv	*g_serv;

/*
**	CLIENT
*/

void	write_log(char *msg, int code);
void	make_intro(void);
int		check_correct(t_read *r);
t_read	*read_init(char **his, char *prompt);
void	read_input(t_sh *shell);
void	delete_read(t_read *read);
char	ft_getchar(void);
void	controlled_termios(t_sh *shell);
void	reset_termios(t_sh *shell);
void	start_termios(t_sh *shell);
int		tab_complete(t_read *read);
int		history_search(t_read *r);
int		paste_str(t_read *read);
int		cut_line_right(t_read *read);
int		cut_line_left(t_read *read);
int		cursor_left_word(t_read *read);
int		cursor_right_word(t_read *read);
int		cursor_up_key(t_read *read);
int		cursor_down_key(t_read *read);
int		cursor_left_key(t_read *read);
int		cursor_right_key(t_read *read);
int		delete_key(t_read *read);
int		backspace(t_read *read);
int		history_up(t_read *read);
int		history_down(t_read *read);
int		reset_line(t_read *read);
int		end_reading(t_read *read);
int		termcap_home(t_read *read);
int		termcap_end(t_read *read);
int		term_go_backward(t_read *r);
int		term_go_forward(t_read *r);
void	print_str(t_read *read);
void	update_history(t_sh *shell);
int		insert_enter(t_read *read);
void	print_rest(t_read *read);
void	place_cursor(t_read *read);
void	get_line(t_read *read);
int		termcap_home(t_read *r);
int		processing_key(t_read *read);
void	get_line_again(t_read *read);
int		check_correct(t_read *read);
void	insert_char(t_read *read, char key);
void	delete_read(t_read *read);
int		termcap_do(char *key);
void	termcap_cursor(t_read *read);
int		termcap_goto(char *key, int col, int row);
void	print(t_read *read);
int		actions_regular(t_read *read);
int		actions_extended(t_read *read);

/*
**	SERVER
*/

void	exit_taskmaster(void);
int		take_signal(char *line);
char	*start_proc(char **argv);
char	**take_env(char **env, char **map, int *pos);
int		take_autorestart(char *line);
int		take_autostart(char *line);
char	**take_file(int fd);
char	*take_string(char *line, char *param, int size);
int		*take_exit(char *line, char *param, int size);
int		take_num(char *line, char *param, int size);
void	config_error(void);
void	ft_lstpushback(t_list **lst, void *content, size_t size);
char	**ft_arrdup(char **s);
void	ft_delete_list(t_list *lst);
char	**make_argv(char *content);
char	*take_cmd(char *line);
void	dup_process(t_jobs *jobs);
void	kill_it(t_jobs *job);
void	handler(int sig);
void	control_proc(t_jobs *job, int status);
void	change_state(t_jobs *start, int tmp, int status);
char	**make_argv(char *content);
t_jobs	*load_jobs(char **env);
void	load_programs(t_jobs *job);
void	fork_it(t_jobs *job);
void	delete_job(t_jobs *job);
void	reload_config(t_jobs *reload, t_jobs *begin, t_jobs *tmp);
void	monitoring(pid_t tmp, int status);
t_jobs	*check_timing(void);
void	control_timing(t_jobs *job);
void	change_stat(int tmp, int status, t_jobs *job);
void	set_settings(t_jobs *job);
char	*help(char *(*f)(const char*, const char*));
char	*reload(void);
int		check_time(time_t time, int sec);
char	*make_response(char **argv);
void	set_status(char **ret, t_jobs *job);
char	*stop_proc(char **argv);
char	*continue_proc(char **argv);
char	*kill_proc(char **argv);
char	*restart_proc(char **argv);

#endif
