/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_expand_op.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesim <sesim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 18:30:32 by sesim             #+#    #+#             */
/*   Updated: 2022/10/21 18:22:58 by sesim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vector	vec_min(t_vector cmp_vec, t_vector standard)
{
	if (cmp_vec.x > standard.x)
		cmp_vec.x = standard.x;
	if (cmp_vec.y > standard.y)
		cmp_vec.y = standard.y;
	if (cmp_vec.z > standard.z)
		cmp_vec.z = standard.z;
	return (cmp_vec);
}

t_vector	vec_once_add_point(t_point o, t_vector *a, \
								t_vector *b, t_vector *c)
{
	t_vector	init;

	init.x = o.x + a->x + b->x + c->x;
	init.y = o.y + a->y + b->y + c->y;
	init.z = o.z + a->z + b->z + c->z;
	return (init);
}

t_vector	vec_mul_const(t_vector *u, double n)
{
	t_vector	init;

	init.x = u->x * n;
	init.y = u->y * n;
	init.z = u->z * n;
	return (init);
}

t_vector	vec_mul_matrix(t_matrix *matrix, t_vector *n)
{
	t_vector	init;

	init.x = n->x * matrix[0].x + n->y * matrix[0].y + n->z * matrix[0].z;
	init.y = n->x * matrix[1].x + n->y * matrix[1].y + n->z * matrix[1].z;
	init.z = n->x * matrix[2].x + n->y * matrix[2].y + n->z * matrix[2].z;
	return (init);
}

t_vector	vec_div_const(t_vector *u, double n)
{
	return (vec_mul_const(u, (1 / n)));
}
