/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesim <sesim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 18:30:30 by sesim             #+#    #+#             */
/*   Updated: 2022/10/16 18:38:57 by sesim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	vec_dot(t_vector u, t_vector v)
{
	return (u.x * v.x + u.y * v.y + u.z * v.z);
}

double	vec_len_pow(t_vector u)
{
	double	pow_val[3];

	pow_val[X] = u.x * u.x;
	pow_val[Y] = u.y * u.y;
	pow_val[Z] = u.z * u.z;
	return (pow_val[X] + pow_val[Y] + pow_val[Z]);
}

double	vec_len(t_vector u)
{
	return (sqrt(vec_len_pow(u)));
}

t_vector	vec_cross(t_vector u, t_vector v)
{
	t_vector	init;

	init.x = u.y * v.z - u.z * v.y;
	init.y = u.z * v.x - u.x * v.z;
	init.z = u.x * v.y - u.y * v.x;
	return (init);
}

t_vector	vec_unit(t_vector u)
{
	return (vec_div_const(u, vec_len(u)));
}
