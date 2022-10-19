/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_slave.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesim <sesim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 11:26:26 by sesim             #+#    #+#             */
/*   Updated: 2022/10/19 20:06:56 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "my_func.h"
#include "minirt.h"
#include "minirt_bonus.h"

void	*ft_rendering(void *param)
{
	t_thread *const	slave = (t_thread *)param;
	int				idx[2];
	double			vdx[2];
	int				section;
	t_color			color;

	section = WIN_H / PHILO_N;
	idx[Y] = (section * slave->idx) - 1;
	while (++idx[Y] < section * (slave->idx + 1))
	{
		idx[X] = -1;
		while (++idx[X] < WIN_W)
		{
			vdx[U] = (double)idx[X] / (WIN_W - 1);
			vdx[V] = (double)idx[Y] / (WIN_H - 1);
			set_ray_vec(&slave->rec.ray, slave->info->camera, vdx[U], vdx[V]);
			color = cur_point_color(slave->info, &slave->rec);
			my_mlx_pixel_put(&slave->info->mlx.img, idx[X], (WIN_H - 1 - idx[Y]), color);
		}
	}
	printf("msg: slave <%d> done\n", slave->idx);
	return (NULL);
}
