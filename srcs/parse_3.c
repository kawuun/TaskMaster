/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvdovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 12:13:50 by dvdovenk          #+#    #+#             */
/*   Updated: 2017/11/13 12:13:51 by dvdovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_lib.h"

static t_list	*make_dup(t_list *lst, char *s, int save, int i)
{
	char	*tmp;

	tmp = ft_strsub(s, save, i - save);
	ft_lstpushback(&lst, tmp, i - save + 1);
	ft_strdel(&tmp);
	return (lst);
}

static t_list	*ft_separate(char *s, char c, t_list *lst, int i)
{
	int save;

	while (s[i])
	{
		while (s[i] && (s[i] ^ c) == 0)
			i++;
		save = i;
		while (s[i] && (s[i] ^ c) != 0)
			i++;
		if (save != i)
			lst = make_dup(lst, s, save, i);
	}
	return (lst);
}

static int		ft_take_size(t_list *content)
{
	int	i;

	i = 0;
	while (content)
	{
		content = content->next;
		i++;
	}
	return (i);
}

char			**make_argv(char *content)
{
	char	**argv;
	t_list	*lst;
	t_list	*s;
	size_t	i;

	argv = NULL;
	if ((lst = ft_separate(content, ' ', NULL, 0)))
	{
		argv = (char**)ft_memalloc(sizeof(char*) * (ft_take_size(lst) + 1));
		i = -1;
		s = lst;
		while (lst)
		{
			argv[++i] = ft_strdup(lst->content);
			lst = lst->next;
		}
		argv[++i] = NULL;
		ft_delete_list(s);
	}
	return (argv);
}

char			*take_cmd(char *line)
{
	int		size;

	if (!line)
		config_error();
	if (!ft_strnequ(line, "cmd: \"", 6))
		config_error();
	line += 6;
	size = ft_strlen(line);
	if (line[size - 1] != '\"')
		config_error();
	line[size - 1] = '\0';
	return (ft_strdup(line));
}
