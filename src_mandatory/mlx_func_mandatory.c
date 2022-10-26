/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_func_mandatory.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesim <sesim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 14:30:00 by sesim             #+#    #+#             */
/*   Updated: 2022/10/26 13:17:07 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "minirt.h"
#include "minirt_mandatory.h"
#include "my_func.h"
#include "mlx_key_func.h"
#include "mlx.h"

static void	_press_esc(t_info *info, t_mlx *mlx)
{
	mlx_destroy_image(mlx->ptr, mlx->img.img_ptr);
	mlx_clear_window(mlx->ptr, mlx->win);
	mlx_destroy_window(mlx->ptr, mlx->win);
	info_free(info, mlx);
	exit(0);
}

static void	_main_loop(t_info *info, t_mlx *mlx, int key, \
						void (*event)(t_info *, int))
{
	mlx_destroy_image(mlx->ptr, mlx->img.img_ptr);
	mlx_clear_window(mlx->ptr, mlx->win);
	mlx->img.img_ptr = mlx_new_image(mlx->ptr, WIN_W, WIN_H);
	mlx->img.addr = mlx_get_data_addr(mlx->img.img_ptr, \
									&(mlx->img.bits_per_pixel), \
									&(mlx->img.line_length), \
									&(mlx->img.endian));
	event(info, key);
	ft_draw(info, mlx);
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img.img_ptr, 0, 0);
}

int	mouse_compatible_param(int button, int x, int y, void *param)
{
	t_info *const	info = (t_info *)param;

	(void)x;
	(void)y;
	_main_loop(info, &info->mlx, button, mouse_event);
	return (0);
}

int	key_compatible_param(int keycode, void *param)
{
	t_info *const	info = (t_info *)param;

	if (keycode == KEY_ESC)
		_press_esc(info, &info->mlx);
	_main_loop(info, &info->mlx, keycode, key_event);
	return (0);
}

int	exit_compatible_param(void *param)
{
	t_info *const	info = (t_info *)param;

	_press_esc(info, &info->mlx);
	return (0);
}
