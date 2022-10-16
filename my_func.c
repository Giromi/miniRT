/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_func.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesim <sesim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 18:07:41 by sesim             #+#    #+#             */
/*   Updated: 2022/10/16 18:07:50 by sesim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	my_open(const char *path, int oflag)
{
	int	fd;

	fd = open(path, oflag);
	if (fd < 0)
		ft_strerror("err: cannot open file");
	return (fd);
}

void	*my_calloc(size_t count, size_t size)
{
	void	*res;

	res = ft_calloc(count, size);
	if (!res)
		ft_strerror("err: cannot allocate");
	return (res);
}

char	**my_split(char *line, char c)
{
	char	**split;

	split = ft_split(line, c);
	if (split == NULL)
		ft_strerror("err: allocation failed");
	return (split);
}
