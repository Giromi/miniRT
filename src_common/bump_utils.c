/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesim <sesim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 18:23:09 by sesim             #+#    #+#             */
/*   Updated: 2022/10/19 15:04:02 by sesim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "my_func.h"
#include "minirt.h"

static t_vector	_convert_color_to_normal(int color)
{
	t_vector	cal_val[2];
	t_vector	res;

	res.x = color >> 16 & 0xFF;
	res.y = color >> 8 & 0xFF;
	res.z = color & 0xFF;
	if ((res.x == 0 && res.y == 0 && res.z == 0))
		ft_strerror("err: worng bump map");
	res = vec_div_const(&res, 255);
	cal_val[ONE] = vec_mul_const(&res, 2);
	cal_val[TWO] = vec_init(1, 1, 1);
	res = vec_sub(&cal_val[ONE], &cal_val[TWO]);
	return (res);
}

static t_vector	_convert_int_to_rgb(int color)
{
	t_vector	res;

	res.x = color >> 16 & 0xFF;
	res.y = color >> 8 & 0xFF;
	res.z = color & 0xFF;
	return (res);
}

static t_vector	_tex_rgb(t_object *obj, t_moment *spot)
{
	t_vector	tmp;
	int			x;
	int			y;

	x = (int)(spot->uv_dir[U] * obj->tex->width);
	y = (int)(spot->uv_dir[V] * obj->tex->height);
	tmp = _convert_int_to_rgb(*(unsigned int *)(obj->tex->addr + \
								x * obj->tex->bits_per_pixel / 8 + \
								y * obj->tex->line_length));
	return (vec_div_const(&tmp, 255));
}

static t_vector	_bump_normal(t_object *obj, t_moment *spot)
{
	t_vector	vec[4];
	int			x;
	int			y;

	x = (int)(spot->uv_dir[U] * (double)(obj->bump->width - 1));
	y = (int)(spot->uv_dir[V] * (double)(obj->bump->height - 1));
	vec[NORMAL] = _convert_color_to_normal(*(unsigned int *)(obj->bump->addr + \
								x * obj->bump->bits_per_pixel / 8 + \
								y * obj->bump->line_length));
	vec[X] = vec_mul_const(&spot->e_[ONE], vec[NORMAL].x);
	vec[Y] = vec_mul_const(&spot->e_[TWO], vec[NORMAL].y);
	vec[Z] = vec_mul_const(&spot->normal, vec[NORMAL].z);
	vec[NORMAL] = vec_once_add_point(vec_init(0, 0, 0), \
									&vec[X], &vec[Y], &vec[Z]);
	return (vec_unit(&vec[NORMAL]));
}

void	get_bump_rgb(t_moment *spot, t_object *obj)
{
	spot->albedo = obj->albedo;
	if (!(obj->type & BM))
		return ;
	if (obj->tex && obj->tex->img_ptr)
		spot->albedo = _tex_rgb(obj, spot);
	spot->normal = _bump_normal(obj, spot);
}
