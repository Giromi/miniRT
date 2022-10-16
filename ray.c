/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesim <sesim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 18:29:23 by sesim             #+#    #+#             */
/*   Updated: 2022/10/16 18:29:35 by sesim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	is_t_in_range(t_moment *spot)
{
	return (spot->tmin <= spot->t && spot->t <= spot->tmax);
}

int	is_h_in_range(double h, double h_prime)
{
	return (0 <= h_prime && h_prime <= h);
}

t_point	ray_at(t_ray ray, double t)
{
	t_point	at;

	at = vec_add(ray.orig, vec_mul_const(ray.dir, t));
	return (at);
}
