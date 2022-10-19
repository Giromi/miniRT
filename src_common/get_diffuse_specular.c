/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_diffuse_specular.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesim <sesim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 18:05:13 by sesim             #+#    #+#             */
/*   Updated: 2022/10/19 14:38:48 by sesim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "minirt.h"

static int	_in_shadow(t_object *objs, t_ray *light_ray, double light_len)
{
	t_moment	spot;

	spot.t_[MIN] = 0;
	spot.t_[MAX] = light_len;
	if (is_ray_hit(objs, light_ray, &spot))
		return (TRUE);
	return (FALSE);
}

static void	_convert_reflect_vec(t_vector *reflect, t_vector l, t_vector n)
{
	double	alpha;

	alpha = vec_dot(&l, &n);
	reflect[COMPUTE] = vec_mul_const(&n, 2 * alpha);
	reflect[DIR] = vec_sub(&reflect[COMPUTE], &l);
}

static t_ray	_ray_init(t_point orig, t_vector dir)
{
	t_ray	init;

	init.orig = orig;
	init.dir = vec_unit(&dir);
	return (init);
}

int	get_diffuse(t_info *info, t_light *cur_light, t_vector *light)
{
	t_ray		ray;
	t_vector	vec[2];
	double		val[2];

	light[DIR] = vec_sub(&cur_light->origin, &info->spot.p);
	vec[GAP] = vec_mul_const(&info->spot.normal, EPSILON);
	vec[OFFSET] = vec_add(&info->spot.p, &vec[GAP]);
	ray = _ray_init(vec[OFFSET], light[DIR]);
	val[LEN] = vec_len(&light[DIR]);
	if (_in_shadow(info->obj, &ray, val[LEN]))
		return (ERROR);
	light[DIR] = vec_unit(&light[DIR]);
	val[KD] = fmax(vec_dot(&info->spot.normal, &light[DIR]), 0.0);
	light[DIFFUSE] = vec_mul_const(&cur_light->light_color, val[KD]);
	return (TRUE);
}

void	get_specular(t_info *info, t_light *cur_light, t_vector *light)
{
	t_vector	reflect[2];
	t_vector	view[2];
	double		reflect_cos;
	double		blink_ratio;

	view[COMPUTE] = vec_mul_const(&info->ray.dir, -1);
	view[DIR] = vec_unit(&view[COMPUTE]);
	_convert_reflect_vec(reflect, light[DIR], info->spot.normal);
	reflect_cos = fmax(vec_dot(&view[DIR], &reflect[DIR]), 0.0);
	blink_ratio = pow(reflect_cos, KSN);
	light[SPECULAR] = vec_mul_const(&cur_light->light_color, KS);
	light[SPECULAR] = vec_mul_const(&light[SPECULAR], blink_ratio);
}
