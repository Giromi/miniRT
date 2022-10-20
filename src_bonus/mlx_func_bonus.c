/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_func_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesim <sesim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 14:05:56 by sesim             #+#    #+#             */
/*   Updated: 2022/10/20 17:29:48 by sesim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "minirt.h"
#include "minirt_bonus.h"

static void	_press_esc(t_thread *slave, t_info *info, t_mlx *mlx)
{
	(void)info;
	(void)slave;
	mlx_destroy_image(mlx->ptr, mlx->img.img_ptr);
	mlx_clear_window(mlx->ptr, mlx->win);
	mlx_destroy_window(mlx->ptr, mlx->win);
	// free_info(info);
	// slave_is_free(slave);
	exit(0);
}

static void	_main_loop(t_thread *slave, t_mlx *mlx, int key)
{
	mlx_destroy_image(mlx->ptr, mlx->img.img_ptr);
	mlx_clear_window(mlx->ptr, mlx->win);
	mlx->img.img_ptr = mlx_new_image(mlx->ptr, WIN_W, WIN_H);
	mlx->img.addr = mlx_get_data_addr(mlx->img.img_ptr, \
									&(mlx->img.bits_per_pixel), \
									&(mlx->img.line_length), \
									&(mlx->img.endian));
	key_event(slave->info, key);
	slave_whip(slave);
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img.img_ptr, 0, 0);
}

int	key_compatible_param(int keycode, void *param)
{
	t_thread *const	slave = (t_thread *)param;

	if (keycode == KEY_ESC)
		_press_esc(slave, slave->info, &slave->info->mlx);
	_main_loop(slave, &slave->info->mlx, keycode);
	return (0);
}