/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_one_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesim <sesim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 11:53:34 by sesim             #+#    #+#             */
/*   Updated: 2022/10/16 20:09:58 by sesim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*_reader(int fd, char *bac)
{
	char	*buf;
	ssize_t	r_cnt;

	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (buf == 0)
		return (0);
	r_cnt = 1;
	while (!ft_strchr_g(bac, '\n') && r_cnt != 0)
	{
		r_cnt = read(fd, buf, BUFFER_SIZE);
		if (r_cnt == -1)
			break ;
		buf[r_cnt] = '\0';
		bac = ft_strjoin_g(bac, buf);
	}
	free(buf);
	buf = 0;
	return (bac);
}

static char	*_get_line(char *bac)
{
	char	*line;
	int		len;

	if (bac[0] == 0)
		return (0);
	if (ft_strchr_g(bac, '\n'))
		len = ft_strchr_g(bac, '\n') - bac + 1;
	else
		len = ft_strlen_g(bac) + 1;
	line = malloc(sizeof(char) * len);
	if (line == 0)
		return (0);
	ft_strlcpy_g(line, bac, len);
	return (line);
}

static t_line	*_get_node(t_line *head, int fd)
{
	t_line	*node;

	node = head->next;
	while (node)
	{
		if (node->idx == fd)
			return (node);
		else
			node = node->next;
	}
	node = malloc(sizeof(t_line));
	if (node == 0)
		return (0);
	node->prev = head;
	node->next = head->next;
	node->idx = fd;
	node->line = 0;
	if (node->next)
		head->next->prev = node;
	head->next = node;
	return (node);
}

static void	_del_node(t_line **node)
{
	free((*node)->line);
	(*node)->line = 0;
	if ((*node)->next)
		(*node)->next->prev = (*node)->prev;
	(*node)->prev->next = (*node)->next;
	free (*node);
	*node = 0;
}

char	*get_one_line(int fd)
{
	static t_line	head;
	t_line			*bac;
	char			*res;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	bac = _get_node(&head, fd);
	if (bac == 0)
		return (0);
	bac->line = _reader(fd, bac->line);
	if (bac->line == 0)
	{
		_del_node(&bac);
		return (0);
	}
	res = _get_line(bac->line);
	if (res == 0)
	{
		_del_node(&bac);
		return (0);
	}
	bac->line = new_line(bac->line);
	if (bac->line == 0)
		_del_node(&bac);
	return (res);
}
