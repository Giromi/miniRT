/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_at_conlinder.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesim <sesim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 18:19:51 by sesim             #+#    #+#             */
/*   Updated: 2022/10/17 16:09:30 by sesim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	_get_conlinder_uv(t_moment *spot, t_model *cny, double size)
{
	const t_vector	n = cny->normal;
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
	p_[E_ONE] = vec_dot(vec_sub(spot->p, cny->center), spot->e1);
	p_[E_TWO] = vec_dot(vec_sub(spot->p, cny->center), spot->e2);
	theta = atan2(p_[E_TWO], p_[E_ONE]);
	spot->u = (theta / (M_PI));
	spot->v = fmod(vec_dot(vec_sub(spot->p, cny->center), n) \
				/ (cny->radius * M_PI), 1);
	spot->u += spot->u < 0;
	spot->v = 1 - spot->v;
	spot->u = fmod(spot->u, size) / size;
	spot->v = fmod(spot->v, size) / size;
}

static void	_get_cy_side_normal(t_moment *spot, t_model *cy, \
									t_vector *coor, double h_prime)
{
	coor[C_Q] = vec_mul_const(cy->normal, h_prime);
	spot->normal = vec_sub(coor[C_P], coor[C_Q]);
	spot->normal = vec_unit(spot->normal);
	_get_conlinder_uv(spot, cy, 1);
}

static int	_get_cn_side_normal(t_moment *spot, t_conlinder *cn, \
								t_vector *coor)
{
	t_vector	ac_vec;
	double		val[3];

	coor[C_H] = vec_mul_const(cn->normal, cn->height);
	val[NUMERATOR] = vec_len_pow(vec_sub(coor[C_P], coor[C_H]));
	if (fabs(val[NUMERATOR]) < EPSILON)
		return (ERROR);
	val[DENOMINATOR] = cn->height - vec_dot(coor[C_P], cn->normal);
	val[TARGET] = cn->height - (val[NUMERATOR] / val[DENOMINATOR]);
	ac_vec = vec_mul_const(cn->normal, val[TARGET]);
	spot->normal = vec_sub(coor[C_P], ac_vec);
	spot->normal = vec_unit(spot->normal);
	_get_conlinder_uv(spot, cn, 1);
	return (TRUE);
}

int	ray_at_conlinder(t_object *obj, t_ray ray, t_moment *spot, \
					void (*get_abc)(double *term, t_ray *ray, t_model *cy))
{
	t_conlinder *const	cny = obj->elem;
	t_vector			coor[2];
	t_function			func;

	if (get_2d_root(&func, &ray, cny, get_abc) == ERROR)
		return (FALSE);
	spot->t = func.root[0];
	if (!is_t_in_range(spot))
	{
		spot->t = func.root[1];
		if (!is_t_in_range(spot))
			return (FALSE);
	}
	spot->p = ray_at(ray, spot->t);
	coor[C_P] = vec_sub(spot->p, cny->center);
	func.h_prime = (vec_dot(coor[C_P], cny->normal));
	if (!is_h_in_range(cny->height, func.h_prime))
		return (FALSE);
	if (obj->type & CY) 
		_get_cy_side_normal(spot, cny, coor, func.h_prime);
	else if (obj->type & CN)
		_get_cn_side_normal(spot, cny, coor);
	get_bump_rgb(spot, obj);
	flip_normal_face(ray, spot);
	return (TRUE);
}

// int	ray_at_cone(t_object *obj, t_ray ray, t_moment *spot)
// {
// 	t_conlinder *const	cn = obj->elem;
// 	t_vector			coor[2];
// 	t_function			func;

// 	if (get_2d_root(&func, &ray, cn, get_cn_abc) == ERROR)
// 		return (FALSE);
// 	func.i = -1;
// 	while (++func.i < 2)
// 	{
// 		spot->t = func.root[func.i];
// 		if (!is_t_in_range(spot))
// 			continue ;
// 		spot->p = ray_at(ray, spot->t);
// 		coor[C_P] = vec_sub(spot->p, cn->center);
// 		func.h_prime = (vec_dot(coor[C_P], cn->normal));
// 		if (is_h_in_range(cn->height, func.h_prime))
// 			break ;
// 		if (func.i == 1)
// 			return (FALSE);
// 	}
// 	if (_get_cn_side_normal(spot, cn, coor) == ERROR)
// 		return (FALSE);
// 	get_bump_rgb(spot, obj);
// 	flip_normal_face(ray, spot);
// 	return (TRUE);
// }

// int	ray_at_cylinder(t_object *obj, t_ray ray, t_moment *spot)
// {
// 	t_conlinder *const	cy = obj->elem;
// 	t_vector			coor[2];
// 	t_function			func;

// 	if (get_2d_root(&func, &ray, cy, get_cy_abc) == ERROR)
// 		return (FALSE);
// 	while (++func.i < 2)
// 	{
// 		spot->t = func.root[func.i];
// 		if (!is_t_in_range(spot) && func.i == 0)
// 			continue ;
// 		spot->p = ray_at(ray, spot->t);
// 		coor[C_P] = vec_sub(spot->p, cy->center);
// 		func.h_prime = (vec_dot(coor[C_P], cy->normal));
// 		if (is_h_in_range(cy->height, func.h_prime))
// 			break ;
// 		if (func.i == 1)
// 			return (FALSE);
// 	}
// 	_get_cy_side_normal(spot, cy, coor, func.h_prime);
// 	get_bump_rgb(spot, obj);
// 	flip_normal_face(ray, spot);
// 	return (TRUE);
// }