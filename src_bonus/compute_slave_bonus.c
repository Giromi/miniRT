/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_slave_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesim <sesim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 11:26:26 by sesim             #+#    #+#             */
/*   Updated: 2022/10/20 15:33:01 by sesim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "my_func.h"
#include "minirt.h"
#include "minirt_bonus.h"
#include <unistd.h>

static void	*_ft_rendering(void *param)
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
			set_ray_vec(&slave->rec.ray, slave->info->camera, idx[X], idx[Y]);
			color = cur_point_color(slave->info, &slave->rec);
			my_mlx_pixel_put(&slave->info->mlx.img, idx[X], \
												(WIN_H - 1 - idx[Y]), color);
		}
	}
	return (NULL);
}

static void	_my_slave_die(t_thread *slave, char *err, int cnt)
{
	while (--cnt)
		pthread_join(slave[cnt].hand, NULL);
	ft_strerror(err);
}

void	slave_whip(t_thread *slave)
{
	int	i;

	i = -1;
	while (++i < PHILO_N)
		if (pthread_create(&slave[i].hand, NULL, _ft_rendering, &slave[i]))
			_my_slave_die(slave, "err: pthread_create error", i);
	while (i--)
		pthread_join(slave[i].hand, NULL);
}
