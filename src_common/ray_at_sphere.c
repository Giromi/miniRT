/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_at_sphere.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesim <sesim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 18:22:25 by sesim             #+#    #+#             */
/*   Updated: 2022/10/18 20:37:14 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "minirt.h"

void	get_sphere_uv(t_moment *spot, t_model *sp, double size)
{
	const t_vector	n = spot->normal;
	t_vector		basis_vec;
	double			phi;
	double			theta;

	if ((n.x == 0 && n.y == 1 && n.z == 0))
		basis_vec = vec_init(0, 0, -1);
	else if ((n.x == 0 && n.y == -1 && n.z == 0))
		basis_vec = vec_init(0, 0, 1);
	else
		basis_vec = vec_init(0, 1, 0);
	spot->e1 = vec_unit(vec_cross(basis_vec, n));
	spot->e2 = vec_unit(vec_cross(n, spot->e1));
	theta = atan2((spot->p.x - sp->center.x), (spot->p.z - sp->center.z));
	phi = acos((spot->p.y - sp->center.y) / sp->radius);
	spot->u = (theta / (M_PI));
	spot->v = phi / M_PI;
	spot->u += spot->u < 0;
	spot->u = fmod(spot->u, size) / size;
	spot->v = fmod(spot->v, size) / size;
}

int	ray_at_sphere(t_object *obj, t_ray ray, t_moment *spot)
{
	t_sphere *const	sp = obj->elem;
	t_function		func;
	t_vector		c_p;

	if (get_2d_root(&func, &ray, sp, get_sp_abc) == ERROR)
		return (FALSE);
	func.idx = 0;
	if (!is_t_in_range(spot, func.root[func.idx]))
		if (!is_t_in_range(spot, func.root[++func.idx]))
			return (FALSE);
	spot->t = func.root[func.idx];
	spot->p = get_hit_point(ray, spot->t);
	c_p = vec_sub(spot->p, sp->center);
	spot->normal = vec_div_const(c_p, sp->radius);
	get_sphere_uv(spot, sp, 1);
	get_bump_rgb(spot, obj);
	flip_normal_face(ray, spot);
	return (TRUE);
}
