/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_at_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesim <sesim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 18:29:23 by sesim             #+#    #+#             */
/*   Updated: 2022/10/25 08:43:57 by sesim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "minirt.h"

int	is_t_in_range(t_moment *spot, double root)
{
	return (spot->t_[MIN] <= root && root <= spot->t_[MAX]);
}

int	is_h_in_range(t_model *cny, t_ray *ray, t_vector *coor, t_function *func)
{
	func->hit_p = get_hit_point(ray, func->root[func->idx]);
	coor[C_P] = vec_sub(&func->hit_p, &cny->center);
	func->h_prime = vec_dot(&coor[C_P], &cny->normal);
	return (0 <= func->h_prime && func->h_prime <= cny->height);
}

t_point	get_hit_point(t_ray *ray, double t)
{
	t_point		at;
	t_vector	v;

	v = vec_mul_const(&ray->dir, t);
	at = vec_add(&ray->orig, &v);
	return (at);
}
