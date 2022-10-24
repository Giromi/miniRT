/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_key_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesim <sesim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 15:34:56 by sesim             #+#    #+#             */
/*   Updated: 2022/10/24 22:13:21 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "my_func.h"
#include "rotation_func.h"
#include "mlx.h"
#include "minirt.h"

static void	_set_mlx_vector_r_half2(t_vector mlx_vec[2][2], t_vector *cam_vec,
					double *viewport)
{
	mlx_vec[VAL][HORI] = vec_mul_const(&cam_vec[T], viewport[HORI]);
	mlx_vec[VAL][VERT] = vec_mul_const(&cam_vec[B], viewport[VERT]);
	mlx_vec[R_HALF][HORI] = vec_div_const(&mlx_vec[VAL][HORI], -2);
	mlx_vec[R_HALF][VERT] = vec_div_const(&mlx_vec[VAL][VERT], -2);
}

int	is_rotate_key(int key)
{
	return (key == KEY_UP || key == KEY_DOWN \
			|| key == KEY_LEFT || key == KEY_RIGHT \
			|| key == KEY_COMMA || key == KEY_DOT);
}

int	is_translate_key(int key)
{
	return (key == KEY_W || key == KEY_S \
			|| key == KEY_A || key == KEY_D \
			|| key == KEY_SPC || key == KEY_C);
}

static void	_change_camera(t_info *info, int key)
{
	// if (info->type != CAM_MODE)
	// 	return ;
	if (key == KEY_E)
		info->camera = info->camera->next;
	else if (key == KEY_Q)
		info->camera = info->camera->prev;
}

// static void	_change_object(t_info *info, int key)
// {
// 	if (info->type != EDIT_MODE)
// 		reutrn ;
// 	if (key == KEY_E)
// 		info->camera = info->camera->next;
// 	else if (key == KEY_Q)
// 		info->camera = info->camera->prev;
// 	_translate_object(info->object)
// }
int		is_view_key(int key)
{
	return (key == 18 || key == 19 || key == 20 || key == 29);
}

static void	_move_camera(t_camera *cam, int key)
{
	t_vector move;

	if (!is_translate_key(key))
		return ;
	if (key == KEY_W)
		move = vec_mul_const(&cam->vec[N], 0.3);
	else if (key == KEY_S)
		move = vec_mul_const(&cam->vec[N], -0.3);
	else if (key == KEY_A)
		move = vec_mul_const(&cam->vec[T], -0.3);
	else if (key == KEY_D)
		move = vec_mul_const(&cam->vec[T], 0.3);
	else if (key == KEY_SPC)
		move = vec_mul_const(&cam->vec[B], 0.3);
	else if (key == KEY_C)
		move = vec_mul_const(&cam->vec[B], -0.3);
	if (is_translate_key(key))
		cam->orig = vec_add(&cam->orig, &move);
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
		q_rotation(cam, 15.0, PITCH);
	else if (key == KEY_DOWN)
		q_rotation(cam, -15.0, PITCH);
	else if (key == KEY_LEFT)
		q_rotation(cam, 15.0, YAW);
	else if (key == KEY_RIGHT)
		q_rotation(cam, -15.0, YAW);
	else if (key == KEY_COMMA)
		q_rotation(cam, -15.0, ROLL);
	else if (key == KEY_DOT)
		q_rotation(cam, 15.0, ROLL);
}

// static void	_zoom_camera(t_camera *cam, int key)
// {
//     if (!is_rotate_key(key))
//         return ;
//     if (key == KEY_UP)
//         q_rotation(cam, 15.0, PITCH);
//     else if (key == KEY_DOWN)
//         q_rotation(cam, -15.0, PITCH);
//     else if (key == KEY_LEFT)
//         q_rotation(cam, 15.0, YAW);
//     else if (key == KEY_RIGHT)
//         q_rotation(cam, -15.0, YAW);
//     else if (key == KEY_COMMA)
//         q_rotation(cam, -15.0, ROLL);
//     else if (key == KEY_DOT)
//         q_rotation(cam, 15.0, ROLL);
// }



static void	_translate_camera(t_camera *cam, int key)
{
	_move_camera(cam, key);
	_view_camera(cam, key);
	_rotate_camera(cam, key);
	if (is_translate_key(key) || is_rotate_key(key) || is_view_key(key))
		_set_mlx_vector_r_half2(cam->mlx_vec, cam->vec, cam->viewport);
	cam->start_point = vec_once_add_point(cam->orig, \
									&cam->mlx_vec[R_HALF][HORI], \
									&cam->mlx_vec[R_HALF][VERT], &cam->vec[N]);
}


void	key_event(t_info *info, int key)
{
	_change_camera(info, key);
	_translate_camera(info->camera, key);
	// _change_object(info, key);
}

