/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_alloc_func.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesim <sesim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 18:07:41 by sesim             #+#    #+#             */
/*   Updated: 2022/10/25 12:16:32 by sesim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strerror(char *err);

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
