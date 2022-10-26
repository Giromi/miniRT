/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_key_cam_func.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesim <sesim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 15:34:56 by sesim             #+#    #+#             */
/*   Updated: 2022/10/26 12:23:18 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "minirt.h"
#include "my_func.h"
#include "rotation_func.h"
#include "mlx.h"
#include "mlx_key_func.h"

static void	_set_mlx_vector_r_half2(t_vector mlx_vec[2][2], t_vector *cam_vec,
					double *viewport)
{
	mlx_vec[VAL][HORI] = vec_mul_const(&cam_vec[T], viewport[HORI]);
	mlx_vec[VAL][VERT] = vec_mul_const(&cam_vec[B], viewport[VERT]);
	mlx_vec[R_HALF][HORI] = vec_div_const(&mlx_vec[VAL][HORI], -2);
	mlx_vec[R_HALF][VERT] = vec_div_const(&mlx_vec[VAL][VERT], -2);
}

static void	_switch_camera(t_info *info, int key)
{
	if (key == KEY_E)
		info->cam = info->cam->next;
	else if (key == KEY_Q)
		info->cam = info->cam->prev;
}

static void	_view_camera(t_camera *cam, int key)
{
	if (!is_view_key(key))
		return ;
	if (key == 18)
	{
		cam->vec[T] = vec_init(1, 0, 0);
		cam->vec[B] = vec_init(0, 1, 0);
		cam->vec[N] = vec_init(0, 0, -1);
	}
	else if (key == 19)
	{
		cam->vec[T] = vec_init(1, 0, 0);
		cam->vec[B] = vec_init(0, 0, 1);
		cam->vec[N] = vec_init(0, -1, 0);
	}
	else if (key == 20)
	{
		cam->vec[T] = vec_init(0, 0, -1);
		cam->vec[B] = vec_init(0, 1, 0);
		cam->vec[N] = vec_init(-1, 0, 0);
	}
	else if (key == 29)
	{
		cam->vec[T] = vec_mul_const(&cam->vec[T], -1);
		cam->vec[N] = vec_mul_const(&cam->vec[N], -1);
	}
}

static void	_rotate_camera(t_camera *cam, int key)
{
	if (!is_rotate_key(key))
		return ;
	if (key == KEY_UP)
		cam_rotation(cam, cam->vec, 15.0, PITCH);
	else if (key == KEY_DOWN)
		cam_rotation(cam, cam->vec, -15, PITCH);
	else if (key == KEY_LEFT)
		cam_rotation(cam, cam->vec, 15, YAW);
	else if (key == KEY_RIGHT)
		cam_rotation(cam, cam->vec, -15, YAW);
	else if (key == KEY_COMMA)
		cam_rotation(cam, cam->vec, -15, ROLL);
	else if (key == KEY_DOT)
		cam_rotation(cam, cam->vec, 15, ROLL);
}

void	change_cam(t_info *info, int key)
{
	_switch_camera(info, key);
	translate_center(info->cam, &info->cam->orig, key);
	_view_camera(info->cam, key);
	_rotate_camera(info->cam, key);
	if (is_translate_key(key) || is_rotate_key(key) || is_view_key(key))
		_set_mlx_vector_r_half2(info->cam->mlx_vec, \
								info->cam->vec, info->cam->viewport);
	info->cam->start_point = vec_once_add_point(info->cam->orig, \
									&info->cam->mlx_vec[R_HALF][HORI], \
									&info->cam->mlx_vec[R_HALF][VERT], \
									&info->cam->vec[N]);
}
