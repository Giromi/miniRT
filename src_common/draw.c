/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesim <sesim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 17:58:45 by sesim             #+#    #+#             */
/*   Updated: 2022/10/20 15:19:44 by sesim            ###   ########.fr       */
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

void	set_ray_vec(t_ray *ray, t_camera *cam, int x, int y)
{
	t_vector	ray_vec[2];
	t_vector	rev_orig;
	double		vdx[2];

	ray->orig = cam->orig;
	vdx[U] = (double)x / (WIN_W - 1);
	vdx[V] = (double)y / (WIN_H - 1);
	ray_vec[U] = vec_mul_const(&cam->mlx_vec[U], vdx[U]);
	ray_vec[V] = vec_mul_const(&cam->mlx_vec[V], vdx[V]);
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

t_color	cur_point_color(t_info *info, t_record *rec)
{
	t_vector	background[2];
	t_vector	color[2];
	double		t;

	_record_init(&rec->spot);
	if (is_ray_hit(info->obj, &rec->ray, &rec->spot))
		return (phong_lighting(info, rec));
	else
	{
		t = 0.5 * (rec->ray.dir.y + 1.0);
		color[UP] = vec_init(128, 178, 255);
		color[DOWN] = vec_init(255, 255, 255);
		background[UP] = vec_mul_const(&color[UP], t);
		background[DOWN] = vec_mul_const(&color[DOWN], 1.0 - t);
		return (vec_add(&background[0], &background[1]));
	}
}
