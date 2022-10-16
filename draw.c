/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesim <sesim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 17:58:45 by sesim             #+#    #+#             */
/*   Updated: 2022/10/16 18:03:05 by sesim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	_my_mlx_pixel_put(t_image *img, int x, int y, t_color color)
{
	char	*dst;
	int		coor[2];

	coor[X] = x * (img->bits_per_pixel / 8);
	coor[Y] = y * img->line_length;
	dst = img->addr + coor[X] + coor[Y];
	*(unsigned int *)dst = convert_color(color);
}

static void	_spread_ray(t_ray *ray, t_camera *cam, double u, double v)
{
	t_vector	ray_vec[2];

	ray->orig = cam->orig;
	ray_vec[U] = vec_mul_const(cam->mlx_vec[U], u);
	ray_vec[V] = vec_mul_const(cam->mlx_vec[V], v);
	ray->dir = vec_once_add_point(cam->start_point, ray_vec[U], ray_vec[V], \
											vec_mul_const(cam->orig, -1));
	ray->dir = vec_unit(ray->dir);
}

static void	_record_init(t_moment *spot)
{
	ft_memset(spot, 0, sizeof(t_moment));
	spot->tmin = EPSILON;
	spot->tmax = MAX_VIEW;
}

static t_color	_cur_point_color(t_info *info)
{
	double		t;
	t_vector	background[2];

	_record_init(&(info->spot));
	if (is_ray_hit(info->obj, info->ray, &(info->spot)))
		return (phong_lighting(info));
	else
	{
		t = 0.5 * (info->ray.dir.y + 1.0);
		background[UP] = vec_mul_const(vec_init(255, 255, 255), 1.0 - t);
		background[DOWN] = vec_mul_const(vec_init(128, 178, 255), t);
		return (vec_add(background[0], background[1]));
	}
}

void	ft_draw(t_info *info, t_mlx *mlx)
{
	int			idx[2];
	double		vdx[2];
	t_color		color;

	idx[Y] = WIN_H - 1;
	while (idx[Y] >= 0)
	{
		idx[X] = 0;
		while (idx[X] < WIN_W)
		{
			vdx[U] = (double)idx[X] / (WIN_W - 1);
			vdx[V] = (double)idx[Y] / (WIN_H - 1);
			_spread_ray(&info->ray, info->camera, vdx[U], vdx[V]);
			color = _cur_point_color(info);
			_my_mlx_pixel_put(&mlx->img, idx[X], (WIN_H - 1 - idx[Y]), color);
			idx[X]++;
		}
		idx[Y]--;
	}
}
