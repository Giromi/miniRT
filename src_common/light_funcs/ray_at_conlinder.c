/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_at_conlinder.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesim <sesim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 18:19:51 by sesim             #+#    #+#             */
/*   Updated: 2022/10/26 09:16:47 by sesim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "minirt.h"
#include "light_func.h"

void	get_spot_e_vector(t_moment *spot, t_vector *obj_n, t_vector std_n)
{
	t_vector	cross_val[2];
	t_vector	basis_vec;

	if ((obj_n->x == std_n.x && obj_n->y == std_n.y && obj_n->z == std_n.z))
		basis_vec = vec_init(0, -std_n.z, -std_n.y);
	else if ((obj_n->x == -std_n.x && obj_n->y == -std_n.y \
				&& obj_n->z == -std_n.z))
		basis_vec = vec_init(0, std_n.z, std_n.y);
	else
		basis_vec = vec_init(0, std_n.y, std_n.z);
	cross_val[ONE] = vec_cross(&basis_vec, obj_n);
	spot->e_[ONE] = vec_unit(&cross_val[ONE]);
	cross_val[TWO] = vec_cross(obj_n, &spot->e_[ONE]);
	spot->e_[TWO] = vec_unit(&cross_val[TWO]);
}

static void	_get_conlinder_uv(t_moment *spot, t_model *cny, double size)
{
	t_vector	c_p;
	double		theta;
	double		p_[2];

	get_spot_e_vector(spot, &cny->normal, vec_init(0, 0, 1));
	c_p = vec_sub(&spot->p, &cny->center);
	p_[E_ONE] = vec_dot(&c_p, &spot->e_[ONE]);
	p_[E_TWO] = vec_dot(&c_p, &spot->e_[TWO]);
	theta = atan2(p_[E_TWO], p_[E_ONE]);
	spot->uv_dir[U] = (theta / (M_PI));
	spot->uv_dir[V] = fmod(vec_dot(&c_p, &cny->normal) \
							/ (cny->radius * M_PI), 1);
	spot->uv_dir[U] += spot->uv_dir[U] < 0;
	spot->uv_dir[V] = 1 - spot->uv_dir[V];
	spot->uv_dir[U] = fmod(spot->uv_dir[U], size) / size;
	spot->uv_dir[V] = fmod(spot->uv_dir[V], size) / size;
}

static void	_get_cy_side_normal(t_moment *spot, t_model *cy, \
									t_vector *coor, double h_prime)
{
	coor[C_Q] = vec_mul_const(&cy->normal, h_prime);
	spot->normal = vec_sub(&coor[C_P], &coor[C_Q]);
	spot->normal = vec_unit(&spot->normal);
	_get_conlinder_uv(spot, cy, 1);
}

static int	_get_cn_side_normal(t_moment *spot, t_conlinder *cn, \
								t_vector *coor)
{
	t_vector	ac_vec;
	t_vector	h_p;
	double		val[3];

	coor[C_H] = vec_mul_const(&cn->normal, cn->height);
	h_p = vec_sub(&coor[C_P], &coor[C_H]);
	val[NUMERATOR] = vec_len_pow(&h_p);
	if (fabs(val[NUMERATOR]) < EPSILON)
		return (ERROR);
	val[DENOMINATOR] = cn->height - vec_dot(&coor[C_P], &cn->normal);
	val[TARGET] = cn->height - (val[NUMERATOR] / val[DENOMINATOR]);
	ac_vec = vec_mul_const(&cn->normal, val[TARGET]);
	spot->normal = vec_sub(&coor[C_P], &ac_vec);
	spot->normal = vec_unit(&spot->normal);
	_get_conlinder_uv(spot, cn, 1);
	return (TRUE);
}

int	ray_at_conlinder(t_object *obj, t_ray *ray, t_moment *spot, \
					void (*get_abc)(double *, t_ray *, t_model *))
{
	t_conlinder *const	cny = obj->elem;
	t_vector			coor[2];
	t_function			func;

	if (get_2d_root(&func, ray, cny, get_abc) == ERROR)
		return (FALSE);
	func.idx = 0;
	if (!is_t_in_range(spot, func.root[func.idx]) \
			|| !is_h_in_range(cny, ray, coor, &func))
		if (!is_t_in_range(spot, func.root[++func.idx]) \
			|| !is_h_in_range(cny, ray, coor, &func))
			return (FALSE);
	spot->t_[VAL] = func.root[func.idx];
	spot->p = func.hit_p;
	if (obj->type & CY)
		_get_cy_side_normal(spot, cny, coor, func.h_prime);
	else if (obj->type & CN)
		_get_cn_side_normal(spot, cny, coor);
	get_bump_rgb(spot, obj);
	flip_normal_face(ray, spot);
	return (TRUE);
}
