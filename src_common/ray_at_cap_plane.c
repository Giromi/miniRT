/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_at_plane.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesim <sesim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 18:21:38 by sesim             #+#    #+#             */
/*   Updated: 2022/10/18 20:37:07 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "minirt.h"

static void	_get_cap_uv(t_moment *spot, t_model *pl, double size)
{
	const t_vector	n = pl->normal;
	t_vector		basis_vec;
	double			theta;
	double			p_[2];

	if ((n.x == 0 && n.y == 0 && n.z == 1))
		basis_vec = vec_init(0, 1, 0);
	else if ((n.x == 0 && n.y == 0 && n.z == -1))
		basis_vec = vec_init(0, -1, 0);
	else
		basis_vec = vec_init(0, 0, 1);
	spot->e1 = vec_unit(vec_cross(basis_vec, n));
	spot->e2 = vec_unit(vec_cross(n, spot->e1));
	p_[E_ONE] = vec_dot(vec_sub(spot->p, pl->center), spot->e1);
	p_[E_TWO] = vec_dot(vec_sub(spot->p, pl->center), spot->e2);
	theta = atan2(p_[E_TWO], p_[E_ONE]);
	spot->u = (theta / (M_PI));
	spot->u += spot->u < 0;
	spot->v = vec_len(vec_sub(spot->p, pl->center)) / pl->radius;
	spot->u = fmod(spot->u, size) / size;
	spot->v = fmod(spot->v, size) / size;
}

static void	_get_plane_uv(t_moment *spot, t_point center, double size)
{
	const t_vector		p = vec_sub(spot->p, center);
	const t_vector		n = spot->normal;
	t_vector			basis_vec;

	if ((n.x == 0 && n.y == 1 && n.z == 0))
		basis_vec = vec_init(0, 0, -1);
	else if ((n.x == 0 && n.y == -1 && n.z == 0))
		basis_vec = vec_init(0, 0, 1);
	else
		basis_vec = vec_init(0, 1, 0);
	spot->e1 = vec_unit(vec_cross(basis_vec, n));
	spot->e2 = vec_unit(vec_cross(n, spot->e1));
	spot->u = fmod(vec_dot(spot->e1, p), size) / size;
	spot->v = fmod(vec_dot(spot->e2, p), size) / size;
	spot->u += spot->u < 0;
	spot->v += spot->v < 0;
	spot->v = 1 - spot->v;
}

int	ray_at_cap(t_object *obj, t_ray ray, t_moment *spot)
{
	t_plane *const	cp = obj->elem;
	t_point			hit_p;
	t_vector		vec[2];
	double			val[3];

	val[DENOMINATOR] = vec_dot(ray.dir, cp->normal);
	if (fabs(val[DENOMINATOR]) < EPSILON)
		return (FALSE);
	vec[O_C] = vec_sub(cp->center, ray.orig);
	val[NUMERATOR] = vec_dot(vec[O_C], cp->normal);
	val[TARGET] = val[NUMERATOR] / val[DENOMINATOR];
	if (!is_t_in_range(spot, val[TARGET]))
		return (FALSE);
	hit_p = get_hit_point(ray, val[TARGET]);
	vec[C_P] = vec_sub(hit_p, cp->center);
	if (obj->type & CP && (vec_len_pow(vec[C_P]) > cp->radius * cp->radius))
		return (FALSE);
	spot->t = val[TARGET];
	spot->p = hit_p;
	spot->normal = cp->normal;
	_get_cap_uv(spot, cp, 10);
	get_bump_rgb(spot, obj);
	flip_normal_face(ray, spot);
	return (TRUE);
}

int	ray_at_plane(t_object *obj, t_ray ray, t_moment *spot)
{
	t_plane *const	pl = obj->elem;
	t_vector		o_c;
	double			val[3];

	val[DENOMINATOR] = vec_dot(ray.dir, pl->normal);
	if (fabs(val[DENOMINATOR]) < EPSILON)
		return (FALSE);
	o_c = vec_sub(pl->center, ray.orig);
	val[NUMERATOR] = vec_dot(o_c, pl->normal);
	val[TARGET] = val[NUMERATOR] / val[DENOMINATOR];
	if (!is_t_in_range(spot, val[TARGET]))
		return (FALSE);
	spot->t = val[TARGET];
	spot->p = get_hit_point(ray, val[TARGET]);
	spot->normal = pl->normal;
	_get_plane_uv(spot, pl->center, 10);
	get_bump_rgb(spot, obj);
	flip_normal_face(ray, spot);
	return (TRUE);
}

// int	ray_at_plane(t_object *obj, t_ray ray, t_moment *spot) // backup
// {
//     t_plane *const	pl = obj->elem;
//     t_point			hit_p;
//     t_vector		vec[2];
//     double			val[3];
//
//     val[DENOMINATOR] = vec_dot(ray.dir, pl->normal);
//     if (fabs(val[DENOMINATOR]) < EPSILON)
//         return (FALSE);
//     vec[O_C] = vec_sub(pl->center, ray.orig);
//     val[NUMERATOR] = vec_dot(vec[O_C], pl->normal);
//     val[TARGET] = val[NUMERATOR] / val[DENOMINATOR];
//     if (!is_t_in_range(spot, val[TARGET]))
//         return (FALSE);
//     hit_p = ray_at(ray, val[TARGET]);
//     vec[C_P] = vec_sub(hit_p, pl->center);
//     if (obj->type & CP && (vec_len_pow(vec[C_P]) > pl->radius * pl->radius))
//         return (FALSE);
//     spot->t = val[TARGET];
//     spot->p = hit_p;
//     spot->normal = pl->normal;
//     if (obj->type & PL)
//         _get_plane_uv(spot, pl->center, 10);
//     else
//         _get_cap_uv(spot, pl, 10);
//     get_bump_rgb(spot, obj);
//     flip_normal_face(ray, spot);
//     return (TRUE);
// }
