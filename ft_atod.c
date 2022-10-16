/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesim <sesim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 17:53:47 by sesim             #+#    #+#             */
/*   Updated: 2022/10/16 19:40:11 by sesim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	_is_sign(char *str, int *idx, int *sign)
{
	if ((str[*idx] == '+' || str[*idx] == '-') && ++(*idx))
		if (str[*idx - 1] == '-')
			*sign *= -1.0;
}

static	double	_make_num_front_point(char *str, int *idx, int sign)
{
	int		flag;
	double	res;

	res = 0.0;
	flag = 0;
	while (str[*idx])
	{
		if ((flag++ == 0 && str[*idx] == '.') \
				|| ((!ft_isdigit(str[*idx]) && str[*idx] != '.')))
			ft_strerror("err: bad arguemnts");
		if (str[*idx] == '.' && ++(*idx))
			break ;
		res = (res * 10) + (str[*idx] - '0');
		if ((sign == 1 && res > 2147483647) || (sign == -1 && res > 2147483648))
			ft_strerror("err: exceed size at front point");
		(*idx)++;
	}
	return (res);
}

static	double	_make_num_behind_point(char *str, int *idx)
{
	int		flag;
	double	res;
	double	decimal;

	res = 0.0;
	flag = 0;
	decimal = 0.1;
	if (str[*idx - 1] == '.' && !str[*idx])
		ft_strerror("err: multiple dots");
	while (str[*idx])
	{
		if (!ft_isdigit(str[*idx]))
			ft_strerror("err: bad arguemnts");
		if (flag++ > 6 && ++(*idx))
			continue ;
		res += (str[*idx] - '0') * decimal;
		decimal /= 10;
		(*idx)++;
	}
	return (res);
}

double	ft_atod(char *str)
{
	int		idx;
	int		sign;
	double	res;

	idx = 0;
	sign = 1.0;
	_is_sign(str, &idx, &sign);
	if (!ft_isdigit(str[idx]))
		ft_strerror("err: bad arguemnts");
	res = _make_num_front_point(str, &idx, sign);
	res += _make_num_behind_point(str, &idx);
	if ((sign == 1 && res > 2147483647) || (sign == -1 && res > 2147483648))
		ft_strerror("err: exceed size at behind point");
	return (sign * res);
}
