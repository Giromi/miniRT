/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_at_cap_plane.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesim <sesim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 18:21:38 by sesim             #+#    #+#             */
/*   Updated: 2022/10/25 17:02:26by sesim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "minirt.h"

static void	_get_cap_uv(t_moment *spot, t_model *cp, t_point *c, double size)
{
	t_vector	c_p;
	double		theta;
	double		p_[2];

	get_spot_e_vector(spot, &cp->normal, vec_init(0, 0, 1));
	c_p = vec_sub(&spot->p, c);
	p_[E_ONE] = vec_dot(&c_p, &spot->e_[ONE]);
	p_[E_TWO] = vec_dot(&c_p, &spot->e_[TWO]);
	theta = atan2(p_[E_TWO], p_[E_ONE]);
	spot->uv_dir[U] = (theta / (M_PI));
	spot->uv_dir[U] += spot->uv_dir[U] < 0;
	spot->uv_dir[V] = vec_len(&c_p) / cp->radius;
	spot->uv_dir[U] = fmod(spot->uv_dir[U], size) / size;
	spot->uv_dir[V] = fmod(spot->uv_dir[V], size) / size;
}

static t_point	_swap_center(t_object *obj, t_model *cp)
{
	t_point	c_h;

	if (obj->prev->type & CP)
	{
		c_h = vec_mul_const(&cp->normal, obj->prev->prev->elem->height);
		return (vec_add(&cp->center, &c_h));
	}
	return (cp->center);
}

int	ray_at_cap(t_object *obj, t_ray *ray, t_moment *spot)
{
	t_plane *const	cp = obj->elem;
	t_point			hit_p[2];
	t_vector		vec[2];
	double			val[3];

	hit_p[CENTER] = _swap_center(obj, cp);
	val[DENOMINATOR] = vec_dot(&ray->dir, &cp->normal);
	if (fabs(val[DENOMINATOR]) < EPSILON)
		return (FALSE);
	vec[O_C] = vec_sub(&hit_p[CENTER], &ray->orig);
	val[NUMERATOR] = vec_dot(&vec[O_C], &cp->normal);
	val[TARGET] = val[NUMERATOR] / val[DENOMINATOR];
	if (!is_t_in_range(spot, val[TARGET]))
		return (FALSE);
	hit_p[VAL] = get_hit_point(ray, val[TARGET]);
	vec[C_P] = vec_sub(&hit_p[VAL], &hit_p[CENTER]);
	if (vec_len_pow(&vec[C_P]) > cp->radius * cp->radius)
		return (FALSE);
	spot->t_[VAL] = val[TARGET];
	spot->p = hit_p[VAL];
	spot->normal = cp->normal;
	_get_cap_uv(spot, cp, &hit_p[CENTER], 1);
	get_bump_rgb(spot, obj);
	flip_normal_face(ray, spot);
	return (TRUE);
}

static void	_get_plane_uv(t_moment *spot, t_point center, double size)
{
	t_vector	c_p;

	c_p = vec_sub(&spot->p, &center);
	get_spot_e_vector(spot, &spot->normal, vec_init(0, 1, 0));
	spot->uv_dir[U] = fmod(vec_dot(&spot->e_[ONE], &c_p), size) / size;
	spot->uv_dir[V] = fmod(vec_dot(&spot->e_[TWO], &c_p), size) / size;
	spot->uv_dir[U] += spot->uv_dir[U] < 0;
	spot->uv_dir[V] += spot->uv_dir[V] < 0;
	spot->uv_dir[V] = 1 - spot->uv_dir[V];
}

int	ray_at_plane(t_object *obj, t_ray *ray, t_moment *spot)
{
	t_plane *const	pl = obj->elem;
	t_vector		o_c;
	double			val[3];

	val[DENOMINATOR] = vec_dot(&ray->dir, &pl->normal);
	if (fabs(val[DENOMINATOR]) < EPSILON)
		return (FALSE);
	o_c = vec_sub(&pl->center, &ray->orig);
	val[NUMERATOR] = vec_dot(&o_c, &pl->normal);
	val[TARGET] = val[NUMERATOR] / val[DENOMINATOR];
	if (!is_t_in_range(spot, val[TARGET]))
		return (FALSE);
	spot->t_[VAL] = val[TARGET];
	spot->p = get_hit_point(ray, val[TARGET]);
	spot->normal = pl->normal;
	_get_plane_uv(spot, pl->center, 10);
	get_bump_rgb(spot, obj);
	flip_normal_face(ray, spot);
	return (TRUE);
}
