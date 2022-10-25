/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesim <sesim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 21:38:54 by minsuki2          #+#    #+#             */
/*   Updated: 2022/10/25 18:47:54 by sesim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "my_func.h"
#include "minirt.h"
#include "put_func.h"
#include "rotation_func.h"
#include "minirt_bonus.h"

void	info_error(int *form_check)
{
	if (form_check[A] != 1)
		ft_strerror("err: wrong ambeint format");
	if (form_check[L] < 0)
		ft_strerror("err: wrong light format");
	if (form_check[C] < 1)
		ft_strerror("err: wrong camera format");
}

static t_thread	*_slave_hire(t_info *info)
{
	t_thread	*slave;
	int			i;

	slave = my_calloc(PHILO_N, sizeof(t_thread));
	i = -1;
	while (++i < PHILO_N)
	{
		slave[i].idx = i;
		slave[i].info = info;
	}
	return (slave);
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
	if (slave->info->status & ANTI)
	{
		while (++i < PHILO_N)
		{
			if (pthread_create(&slave[i].hand, NULL, anti_aliaising, &slave[i]))
				_my_slave_die(slave, "err: pthread_create error", i);
		}
	}
	else
	{
		while (++i < PHILO_N)
		{
			if (pthread_create(&slave[i].hand, NULL, rendering, &slave[i]))
				_my_slave_die(slave, "err: pthread_create error", i);
		}
	}
	while (i--)
		pthread_join(slave[i].hand, NULL);
}

int	main(int argc, char **argv)
{
	t_info		info;
	t_thread	*slave;

	if (argc != 2)
		ft_strerror("err: wrong arguments");
	ft_memset(&info, 0, sizeof(t_info));
	info.mlx.ptr = mlx_init();
	info.mlx.win = mlx_new_window(info.mlx.ptr, WIN_W, WIN_H, "miniRT_bonus");
	info.mlx.img.img_ptr = mlx_new_image(info.mlx.ptr, IMG_W, IMG_H);
	info.mlx.img.addr = mlx_get_data_addr(info.mlx.img.img_ptr, \
											&(info.mlx.img.bits_per_pixel), \
											&(info.mlx.img.line_length), \
											&(info.mlx.img.endian));
	info_init(&info, argv[1]);
	slave = _slave_hire(&info);
	slave_whip(slave);
	mlx_put_image_to_window(info.mlx.ptr, info.mlx.win, \
							info.mlx.img.img_ptr, 0, 0);
	mlx_hook(info.mlx.win, EVENT_KEY_PRESS, 0, key_compatible_param, slave);
	mlx_hook(info.mlx.win, EVENT_MOUSE_CLICK, 0, mouse_compatible_param, slave);
	// mlx_hook(fdf.vars.win, EVENT_CLICK_EXIT, 0, exit_hook, slave);
	mlx_loop(info.mlx.ptr);
	return (0);
}
