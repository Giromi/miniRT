/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atovec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesim <sesim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 18:03:29 by sesim             #+#    #+#             */
/*   Updated: 2022/10/16 18:03:31 by sesim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	_check_unit(t_vector *res, int flag)
{
	if (flag == RGB)
	{
		if (res->x > 255 || res->x < 0 \
			|| res->y > 255 || res->y < 0 \
			|| res->z > 255 || res->z < 0)
			ft_strerror("err: exceed RGB value range");
	}
	else if (flag == XYZ || flag == UNIT)
	{
		if (res->x > 2147483647 || res->x < -2147483648 \
			|| res->y > 2147483647 || res->y < -2147483648 \
			|| res->z > 2147483647 || res->z < -2147483648)
			ft_strerror("err: exceed coordinate value range");
		if (flag == UNIT)
		{
			if (res->x == 0 && res->y == 0 && res->z == 0)
				ft_strerror("err: normal vector value is zero");
			*res = vec_unit(vec_init(res->x, res->y, res->z));
		}
	}
}

t_vector	ft_atovec(char *str, int flag)
{
	t_vector	res;
	char		**vec;
	int			i;
	int			cnt;

	cnt = 0;
	i = -1;
	while (str[++i])
		if (str[i] == ',')
			cnt++;
	if (cnt != 2)
		ft_strerror("err: wrong number of values ','");
	vec = ft_split(str, ',');
	i = -1;
	while (vec[++i])
		;
	if (i != 3)
		ft_strerror("err: ',' in a row");
	res.x = ft_atod(vec[0]);
	res.y = ft_atod(vec[1]);
	res.z = ft_atod(vec[2]);
	_check_unit(&res, flag);
	split_free(vec);
	return (res);
}
