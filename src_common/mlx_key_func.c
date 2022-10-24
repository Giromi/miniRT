/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_key_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesim <sesim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 15:34:56 by sesim             #+#    #+#             */
/*   Updated: 2022/10/24 18:21:24 by sesim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "my_func.h"
#include "rotation_func.h"
#include "mlx.h"
#include "minirt.h"

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

static void	_translate_camera(t_camera *cam, int key)
{
	// if (key != KEY_W && key != KEY_A && key != KEY_S && key != KEY_D && \
	// 		key != KEY_SPC && key != KEY_CTRL)
	// 	return ;
	cam->orig.z -= (key == KEY_W) * WEIGHT_VAL_TRANSLATED_CAM;
	cam->orig.z += (key == KEY_S) * WEIGHT_VAL_TRANSLATED_CAM;
	cam->orig.x -= (key == KEY_A) * WEIGHT_VAL_TRANSLATED_CAM;
	cam->orig.x += (key == KEY_D) * WEIGHT_VAL_TRANSLATED_CAM;
	cam->orig.y += (key == KEY_SPC) * WEIGHT_VAL_TRANSLATED_CAM;
	cam->orig.y -= (key == KEY_CTRL) * WEIGHT_VAL_TRANSLATED_CAM;


	if (key == KEY_UP)
		q_rotation(cam, 5.0, PITCH);
	else if (key == KEY_DOWN)
		q_rotation(cam, -5.0, PITCH);
	else if (key == KEY_LEFT)
		q_rotation(cam, 5.0, YAW);
	else if (key == KEY_RIGHT)
		q_rotation(cam, -5.0, YAW);
	else if (key == KEY_COMMA)
		q_rotation(cam, -5.0, ROLL);
	else if (key == KEY_DOT)
		q_rotation(cam, 5.0, ROLL);
	// printf("normal : %lf %lf %lf\n", cam->vec[N].x, cam->vec[N].y, cam->vec[N].z);
	if (is_translate_key(key) || is_rotate_key(key))
		set_mlx_vector_r_half(cam->mlx_vec, cam->vec[N], cam->viewport);

	// cam->vec[N].y += (key == KEY_UP) * WEIGHT_VAL_ROTATED_CAM;
	// cam->vec[N].y -= (key == KEY_DOWN) * WEIGHT_VAL_ROTATED_CAM;
	// cam->vec[N].x -= (key == KEY_LEFT) * WEIGHT_VAL_ROTATED_CAM;
	// cam->vec[N].x -= (key == KEY_DOWN) * WEIGHT_VAL_ROTATED_CAM;
	// cam->vec[N].x += 2 * (cam->vec[N].y < -1) - 2 * (cam->vec[N].y > 1);
	// cam->vec[N].y += 2 * (cam->vec[N].y < -1) - 2 * (cam->vec[N].y > 1);
	// cam->vec[N].z += 2 * (cam->vec[N].y < -1) - 2 * (cam->vec[N].y > 1);
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

