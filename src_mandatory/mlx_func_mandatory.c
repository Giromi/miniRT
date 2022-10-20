/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_func_mandatory.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesim <sesim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 14:30:00 by sesim             #+#    #+#             */
/*   Updated: 2022/10/20 17:30:02 by sesim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "my_func.h"
#include "minirt.h"

static void	_press_esc(t_info *info, t_mlx *mlx)
{
	(void)info;
	mlx_destroy_image(mlx->ptr, mlx->img.img_ptr);
	mlx_clear_window(mlx->ptr, mlx->win);
	mlx_destroy_window(mlx->ptr, mlx->win);
	// free_info(info);
	exit(0);
}

static void	_main_loop(t_info *info, t_mlx *mlx, int key)
{
	mlx_destroy_image(mlx->ptr, mlx->img.img_ptr);
	mlx_clear_window(mlx->ptr, mlx->win);
	mlx->img.img_ptr = mlx_new_image(mlx->ptr, WIN_W, WIN_H);
	mlx->img.addr = mlx_get_data_addr(mlx->img.img_ptr, \
									&(mlx->img.bits_per_pixel), \
									&(mlx->img.line_length), \
									&(mlx->img.endian));
	key_event(info, key);
	ft_draw(info, mlx);
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img.img_ptr, 0, 0);
}

int	key_compatible_param(int keycode, void *param)
{
	t_info *const	info = (t_info *)param;

	if (keycode == KEY_ESC)
		_press_esc(info, &info->mlx);
	_main_loop(info, &info->mlx, keycode);
	return (0);
}