/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesim <sesim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 17:58:45 by sesim             #+#    #+#             */
/*   Updated: 2022/10/19 18:26:29 by sesim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "my_func.h"
#include "minirt.h"

void	my_mlx_pixel_put(t_image *img, int x, int y, t_color color)
{
	char	*dst;
	int		coor[2];

	coor[X] = x * (img->bits_per_pixel / 8);
	coor[Y] = y * img->line_length;
	dst = img->addr + coor[X] + coor[Y];
	*(unsigned int *)dst = convert_color(&color);
}

void	set_ray_vec(t_ray *ray, t_camera *cam, double u, double v)
{
	t_vector	ray_vec[2];
	t_vector	rev_orig;

	ray->orig = cam->orig;
	ray_vec[U] = vec_mul_const(&cam->mlx_vec[U], u);
	ray_vec[V] = vec_mul_const(&cam->mlx_vec[V], v);
	rev_orig = vec_mul_const(&cam->orig, -1);
	ray->dir = vec_once_add_point(cam->start_point, &ray_vec[U], &ray_vec[V], \
									&rev_orig);
	ray->dir = vec_unit(&ray->dir);
}

static void	_record_init(t_moment *spot)
{
	ft_memset(spot, 0, sizeof(t_moment));
	spot->t_[MIN] = EPSILON;
	spot->t_[MAX] = MAX_VIEW;
}

t_color	cur_point_color(t_info *info)
{
	t_vector	background[2];
	t_vector	color[2];
	double		t;

	_record_init(&(info->spot));
	if (is_ray_hit(info->obj, &info->ray, &info->spot))
		return (phong_lighting(info));
	else
	{
		t = 0.5 * (info->ray.dir.y + 1.0);
		color[UP] = vec_init(128, 178, 255);
		color[DOWN] = vec_init(255, 255, 255);
		background[UP] = vec_mul_const(&color[UP], t);
		background[DOWN] = vec_mul_const(&color[DOWN], 1.0 - t);
		return (vec_add(&background[0], &background[1]));
	}
}

void	ft_draw(t_info *info, t_mlx *mlx)
{
	int			idx[2];
	double		vdx[2];
	t_color		color;

	idx[Y] = -1;
	while (++idx[Y] < WIN_H)
	{
		idx[X] = -1;
		while (++idx[X] < WIN_W)
		{
			vdx[U] = (double)idx[X] / (WIN_W - 1);
			vdx[V] = (double)idx[Y] / (WIN_H - 1);
			set_ray_vec(&info->ray, info->camera, vdx[U], vdx[V]);
			color = cur_point_color(info);
			my_mlx_pixel_put(&mlx->img, idx[X], (WIN_H - 1 - idx[Y]), color);
		}
	}
}
