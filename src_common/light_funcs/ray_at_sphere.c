/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_at_sphere.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesim <sesim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 18:22:25 by sesim             #+#    #+#             */
/*   Updated: 2022/10/26 13:12:21 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "minirt.h"
#include "light_func.h"
#include "draw_func.h"
#include <math.h>

void	get_sphere_uv(t_moment *spot, t_model *sp, double size)
{
	double			phi;
	double			theta;

	get_spot_e_vector(spot, &spot->normal, vec_init(0, 1, 0));
	theta = atan2((spot->p.x - sp->center.x), (spot->p.z - sp->center.z));
	phi = acos((spot->p.y - sp->center.y) / sp->radius);
	spot->uv_dir[U] = (theta / (M_PI));
	spot->uv_dir[V] = phi / M_PI;
	spot->uv_dir[U] += spot->uv_dir[U] < 0;
	spot->uv_dir[U] = fmod(spot->uv_dir[U], size) / size;
	spot->uv_dir[V] = fmod(spot->uv_dir[V], size) / size;
}

int	ray_at_sphere(t_object *obj, t_ray *ray, t_moment *spot)
{
	t_sphere *const	sp = obj->elem;
	t_function		func;
	t_vector		c_p;

	if (get_2d_root(&func, ray, sp, get_sp_abc) == ERROR)
		return (FALSE);
	func.idx = 0;
	if (!is_t_in_range(spot, func.root[func.idx]))
		if (!is_t_in_range(spot, func.root[++func.idx]))
			return (FALSE);
	spot->t_[VAL] = func.root[func.idx];
	spot->p = get_hit_point(ray, spot->t_[VAL]);
	c_p = vec_sub(&spot->p, &sp->center);
	spot->normal = vec_div_const(&c_p, sp->radius);
	get_sphere_uv(spot, sp, 1);
	get_bump_rgb(spot, obj);
	flip_normal_face(ray, spot);
	return (TRUE);
}
