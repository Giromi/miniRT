/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_open_and_err_func.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesim <sesim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 18:07:55 by sesim             #+#    #+#             */
/*   Updated: 2022/10/18 14:00:15 by sesim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <fcntl.h>

void	ft_strerror(char *err)
{
	ft_putendl_fd(err, 2);
	exit(1);
}

int	my_open_rt(const char *path, int oflag)
{
	char	*pos;
	int		fd;

	if (!path)
		ft_strerror("err: null file");
	pos = ft_strchr(path, '.');
	if (pos && ft_strncmp(pos, ".rt", 4))
		ft_strerror("err: wrong file format");
	fd = open(path, oflag);
	if (fd < 0)
		ft_strerror("err: cannot open file");
	return (fd);
}
