/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_slave_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesim <sesim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 11:26:26 by sesim             #+#    #+#             */
/*   Updated: 2022/10/25 19:09:44 by sesim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "my_func.h"
#include "minirt.h"
#include "rotation_func.h"
#include "minirt_bonus.h"
#include <unistd.h>

static double	_random_double(void)
{
	return ((double)rand() / (RAND_MAX + 1.0));
}

static t_color	_cur_enhanced_color(t_thread *slave, int *idx)
{
	t_color	color[2];
	double	vdx[2];
	int		sample;

	sample = -1;
	color[0] = vec_init(0, 0, 0);
	while (++sample < SAMPLE_PER_PIXEL)
	{
		vdx[U] = ((double)idx[X] + _random_double()) / (WIN_W - 1);
		vdx[V] = ((double)idx[Y] + _random_double()) / (WIN_H - 1);
		set_ray_vec(&slave->rec.ray, slave->info->cam, vdx);
		color[1] = cur_point_color(slave->info, &slave->rec);
		color[0] = vec_add(&color[0], &color[1]);
	}
	return (vec_div_const(&color[0], SAMPLE_PER_PIXEL));
}

void	*anti_aliaising(void *param)
{
	t_color			color;
	t_thread *const	slave = (t_thread *)param;
	int				idx[2];
	int				section;

	section = WIN_H / PHILO_N;
	idx[Y] = (section * slave->idx) - 1;
	while (++idx[Y] < section * (slave->idx + 1))
	{
		idx[X] = -1;
		while (++idx[X] < WIN_W)
		{
			color = _cur_enhanced_color(slave, idx);
			my_mlx_pixel_put(&slave->info->mlx.img, idx[X], \
												(WIN_H - 1 - idx[Y]), color);
		}
	}
	return (NULL);
}

void	*rendering(void *param)
{
	t_color			color;
	t_thread *const	slave = (t_thread *)param;
	int				idx[2];
	int				section;
	double			vdx[2];

	section = WIN_H / PHILO_N;
	idx[Y] = (section * slave->idx) - 1;
	while (++idx[Y] < section * (slave->idx + 1))
	{
		idx[X] = -1;
		while (++idx[X] < WIN_W)
		{
			vdx[U] = (double)idx[X] / (WIN_W - 1);
			vdx[V] = (double)idx[Y] / (WIN_H - 1);
			set_ray_vec(&slave->rec.ray, slave->info->cam, vdx);
			color = cur_point_color(slave->info, &slave->rec);
			my_mlx_pixel_put(&slave->info->mlx.img, idx[X], \
												(WIN_H - 1 - idx[Y]), color);
		}
	}
	return (NULL);
}
