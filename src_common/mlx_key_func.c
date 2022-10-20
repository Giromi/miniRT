/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_key_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesim <sesim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 15:34:56 by sesim             #+#    #+#             */
/*   Updated: 2022/10/20 23:52:32 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "my_func.h"
#include "minirt.h"

void	rot_z_axis(t_vector *normal, double theta)
{
	double	x;
	double	y;

	x = normal->x;
	y = normal->y;
	normal->x = x * cos(theta * M_PI / 180) - y * sin(theta * M_PI / 180);
	normal->y = x * sin(theta * M_PI / 180) + y * cos(theta * M_PI / 180);
}

void	rot_y_axis(t_vector *normal, double theta)
{
	double	z;
	double	x;

	z = normal->z;
	x = normal->x;

	normal->x = x * cos(theta * M_PI / 180) + z * sin(theta * M_PI / 180);
	normal->z = -x * sin(theta * M_PI / 180) + z * cos(theta * M_PI / 180);
}

void	rot_x_axis(t_vector *normal, double theta)
{
	double	y;
	double	z;

	y = normal->y;
	z = normal->z;
	normal->y = y * cos(theta * M_PI / 180) - z * sin(theta * M_PI / 180);
	normal->z = y * sin(theta * M_PI / 180) + z * cos(theta * M_PI / 180);
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
//
int		is_rotate_key(int key)
{
	return (key == KEY_UP || key == KEY_DOWN \
			|| key == KEY_LEFT || key == KEY_RIGHT \
			|| key == KEY_COMMA || key == KEY_DOT);
}

int		is_translate_key(int key)
{
	return (key == KEY_W || key == KEY_S \
			|| key == KEY_A || key == KEY_D \
			|| key == KEY_SPC || key == KEY_C);
}

int		is_view_key(int key)
{
	return (key == 18 || key == 19 || key == 20);
}

int		is_couple_rot_key(int old_key, int key)
{
	return (((old_key == KEY_UP || old_key == KEY_DOWN) \
			&& (key == KEY_UP || key == KEY_DOWN)) \
			|| ((old_key == KEY_LEFT || old_key == KEY_RIGHT) \
			&& (key == KEY_LEFT || key == KEY_RIGHT)) \
			|| ((old_key == KEY_COMMA || old_key == KEY_DOT) \
			&& (key == KEY_COMMA || key == KEY_DOT)));
}


// t_vector	get_local_x(t_vector *normal)
// {
//     if (veccmp(&normal, vec_init(0, 0, 1))
//         return (vec_init(0, 0, 1));
// }
//
//
void	get_local_lhv(t_camera *cam, t_vector view_vec[2])
{
	if (veccmp(&view_vec[LOOK], vec_init(0, 0, -1)))
		view_vec[HORI] = vec_init(1, 0, 0);
	else if (veccmp(&view_vec[LOOK], vec_init(0, 0, 1)))
		view_vec[HORI] = vec_init(-1, 0, 0);
	else if (veccmp(&view_vec[LOOK], vec_init(-1, 0, 0)))
		view_vec[HORI] = vec_init(0, 0, -1);
	else if (veccmp(&view_vec[LOOK], vec_init(1, 0, 0)))
		view_vec[HORI] = vec_init(0, 0, 1);
	view_vec[HORI] = vec_mul_const(&view_vec[HORI], WEIGHT_VAL_TRANSLATED_CAM);
	view_vec[VERT] = vec_init(0, 1, 0);
	view_vec[LOOK] = cam->normal;
}


static void	_translate_camera(t_camera *cam, int old_key, int key)
{
	t_vector	view_vec[3];
	// if (key != KEY_W && key != KEY_A && key != KEY_S && key != KEY_D && \
	// 		key != KEY_SPC && key != KEY_C)
	// 	return ;
	get_local_lhv(cam, view_vec);
	if (key == 29)
	{
		cam->normal = vec_mul_const(&cam->normal, -1);
		if (is_view_key(old_key))
			cam->old_normal = cam->normal;
	}
	if (key == 18)
		cam->old_normal = vec_init(0, 0, -1);
	else if (key == 19)
		cam->old_normal = vec_init(-1, 0, 0);
	else if (key == 20)
		cam->old_normal = vec_init(0, -1, 0);

	if (is_view_key(key) || is_translate_key(key) \
		|| (is_rotate_key(key) && !is_couple_rot_key(old_key, key)))
		cam->normal = cam->old_normal;

		// if (veccmp(&cam->normal, vec_init(0, 0, -1)))
	if (key == KEY_W)
		cam->orig = vec_add(&cam->orig, &view_vec[LOOK]);
		// cam->orig.z += ((cam->normal.z > 0) - (cam->normal.z < 0)) * WEIGHT_VAL_TRANSLATED_CAM;
	else if (key == KEY_S)
		cam->orig = vec_sub(&cam->orig, &view_vec[LOOK]);
		// cam->orig.z -= ((cam->normal.z > 0) - (cam->normal.z < 0)) * WEIGHT_VAL_TRANSLATED_CAM;
	else if (key == KEY_A)
		cam->orig = vec_sub(&cam->orig, &view_vec[HORI]);
		// cam->orig.x += ((cam->normal.x > 0) - (cam->normal.x < 0)) * WEIGHT_VAL_TRANSLATED_CAM;
	else if (key == KEY_D)
		cam->orig = vec_add(&cam->orig, &view_vec[HORI]);
		// cam->orig.x -= ((cam->normal.x > 0) - (cam->normal.x < 0)) * WEIGHT_VAL_TRANSLATED_CAM;
	else if (key == KEY_SPC)
		cam->orig = vec_add(&cam->orig, &view_vec[VERT]);
		// cam->orig.y += ((cam->normal.y > 0) - (cam->normal.y < 0)) * WEIGHT_VAL_TRANSLATED_CAM;
	else if (key == KEY_C)
		cam->orig = vec_sub(&cam->orig, &view_vec[VERT]);
		// cam->orig.y -= ((cam->normal.y > 0) - (cam->normal.y < 0)) * WEIGHT_VAL_TRANSLATED_CAM;

	// || (is_rotate_key(key) && old != key) <- 그냥 이렇게?
	if (key == KEY_UP)
		rot_x_axis(&cam->normal, 30);
	else if (key == KEY_DOWN)
		rot_x_axis(&cam->normal, -30);
	else if (key == KEY_LEFT)
		rot_z_axis(&cam->normal, 30);
	else if (key == KEY_RIGHT)
		rot_z_axis(&cam->normal, -30);
	else if (key == KEY_COMMA)
		rot_y_axis(&cam->normal, 30);
	else if (key == KEY_DOT)
		rot_y_axis(&cam->normal, -30);
	if (is_rotate_key(key) || is_view_key(key) || is_translate_key(key) || key == 29)
		set_mlx_vector_r_half(cam->mlx_vec, cam->normal, cam->viewport);

	// cam->normal.y += (key == KEY_UP) * WEIGHT_VAL_ROTATED_CAM;
	// cam->normal.y -= (key == KEY_DOWN) * WEIGHT_VAL_ROTATED_CAM;
	// cam->normal.x -= (key == KEY_LEFT) * WEIGHT_VAL_ROTATED_CAM;
	// cam->normal.x -= (key == KEY_DOWN) * WEIGHT_VAL_ROTATED_CAM;
	// cam->normal.x += 2 * (cam->normal.y < -1) - 2 * (cam->normal.y > 1);
	// cam->normal.y += 2 * (cam->normal.y < -1) - 2 * (cam->normal.y > 1);
	// cam->normal.z += 2 * (cam->normal.y < -1) - 2 * (cam->normal.y > 1);
	debugPrintVec("normal", &cam->normal);
	cam->start_point = vec_once_add_point(cam->orig, \
									&cam->mlx_vec[R_HALF][HORI], \
									&cam->mlx_vec[R_HALF][VERT], &cam->normal);
}

void	key_event(t_info *info, int key)
{
	_change_camera(info, key);
	_translate_camera(info->camera, info->mlx.old_key, key);
	// _change_object(info, key);
	info->mlx.old_key = key;
}

