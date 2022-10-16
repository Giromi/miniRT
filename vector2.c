/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesim <sesim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 18:30:32 by sesim             #+#    #+#             */
/*   Updated: 2022/10/16 18:38:58 by sesim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector	vec_min(t_vector vec1, t_vector vec2)
{
	if (vec1.x > vec2.x)
		vec1.x = vec2.x;
	if (vec1.y > vec2.y)
		vec1.y = vec2.y;
	if (vec1.z > vec2.z)
		vec1.z = vec2.z;
	return (vec1);
}

t_vector	vec_once_add_point(t_point o, t_vector a, t_vector b, t_vector c)
{
	t_vector	init;

	init.x = o.x + a.x + b.x + c.x;
	init.y = o.y + a.y + b.y + c.y;
	init.z = o.z + a.z + b.z + c.z;
	return (init);
}

t_vector	vec_mul_const(t_vector u, double n)
{
	t_vector	init;

	init.x = u.x * n;
	init.y = u.y * n;
	init.z = u.z * n;
	return (init);
}

t_vector	vec_div_const(t_vector u, double n)
{
	if (fabs(n) < EPSILON)
		ft_strerror("err: divide with zero");
	return (vec_mul_const(u, (1 / n)));
}
