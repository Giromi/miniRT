/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_key_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesim <sesim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 15:34:56 by sesim             #+#    #+#             */
/*   Updated: 2022/10/21 02:39:47 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "my_func.h"
#include "minirt.h"

void	rot_z_axis(t_vector *normal, double theta)
{
	double	x;
	double	y;

	if (theta == 0)
		return ;
	x = normal->x;
	y = normal->y;
	normal->x = x * cos(theta * M_PI / 180) - y * sin(theta * M_PI / 180);
	normal->y = x * sin(theta * M_PI / 180) + y * cos(theta * M_PI / 180);
}

void	rot_y_axis(t_vector *normal, double theta)
{
	double	z;
	double	x;

	if (theta == 0)
		return ;
	z = normal->z;
	x = normal->x;
	normal->x = x * cos(theta * M_PI / 180) + z * sin(theta * M_PI / 180);
	normal->z = -x * sin(theta * M_PI / 180) + z * cos(theta * M_PI / 180);
}

void	rot_x_axis(t_vector *normal, double theta)
{
	double	y;
	double	z;

	if (theta == 0)
		return ;
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
void	get_local_e_w_s_n_u_d(t_camera *cam, t_vector view_vec[2])
{
	int i;

	if (veccmp(&cam->normal, vec_init(0, 0, -1))
		|| veccmp(&cam->normal, vec_init(0, 1, 0))
		|| veccmp(&cam->normal, vec_init(0, -1, 0)))
		view_vec[EAST_WEST] = vec_init(1, 0, 0);
	else if (veccmp(&cam->normal, vec_init(0, 0, 1)))
		view_vec[EAST_WEST] = vec_init(-1, 0, 0);
	else if (veccmp(&cam->normal, vec_init(-1, 0, 0)))
		view_vec[EAST_WEST] = vec_init(0, 0, -1);
	else if (veccmp(&cam->normal, vec_init(1, 0, 0)))
		view_vec[EAST_WEST] = vec_init(0, 0, 1);

	if (veccmp(&cam->normal, vec_init(0, -1, 0)) \
		|| (veccmp(&cam->normal, vec_init(0, 1, 0))))
		view_vec[SOUTH_NORTH] = vec_init(0, 0, -1);
	else
		view_vec[SOUTH_NORTH] = cam->normal;
	view_vec[UP_DOWN] = vec_init(0, 1, 0);
	i = -1;
	while (++i < 3)
		view_vec[i] = vec_mul_const(&view_vec[i], WEIGHT_VAL_TRANSLATED_CAM);
}


static void	_translate_camera(t_camera *cam, int old_key, int key)
{
	t_vector	view_vec[3];
	int			sign;

	if (!is_translate_key(key) && !is_rotate_key(key) && !is_view_key(key) && key != 29)
		return ;
	get_local_e_w_s_n_u_d(cam, view_vec);
	if (key == 29)
	{
		cam->normal = vec_mul_const(&cam->normal, -1);
		if (is_view_key(old_key))
			cam->old_normal = cam->normal;
	}
	if (key == 18)
		cam->old_normal = vec_init((cam->normal.x >= 0) - (cam->normal.x < 0), 0, 0);
	else if (key == 19)
		cam->old_normal = vec_init(0, (cam->normal.y >= 0) - (cam->normal.y < 0), 0);
	else if (key == 20)
		cam->old_normal = vec_init(0, 0, (cam->normal.z >= 0) - (cam->normal.z < 0));
	// -> 바라보는 방향으로 초기화 해주기(바꾸고 싶다면 0 버튼 누르기)

	if (is_view_key(key) || is_translate_key(key) \
		|| (is_rotate_key(key) && !is_couple_rot_key(old_key, key)))
		cam->normal = cam->old_normal;
	// -> 사용자가 움직이려고 하면 최대한
	// 일단 첫트에서만 이렇게 오일러 회전으로 통과하기

		// if (veccmp(&cam->normal, vec_init(0, 0, -1)))
	if (key == KEY_W)
		cam->orig = vec_add(&cam->orig, &view_vec[SOUTH_NORTH]);
	else if (key == KEY_S)
		cam->orig = vec_sub(&cam->orig, &view_vec[SOUTH_NORTH]);
	else if (key == KEY_A)
		cam->orig = vec_sub(&cam->orig, &view_vec[EAST_WEST]);
	else if (key == KEY_D)
		cam->orig = vec_add(&cam->orig, &view_vec[EAST_WEST]);
	else if (key == KEY_SPC)
		cam->orig = vec_add(&cam->orig, &view_vec[UP_DOWN]);
	else if (key == KEY_C)
		cam->orig = vec_sub(&cam->orig, &view_vec[UP_DOWN]);
	//		-> 만약에 마크처럼 움직이고 싶으면 이걸 사용

	// if (key == KEY_W)
	//     // cam->orig.z += ((cam->normal.z > 0) - (cam->normal.z < 0)) * WEIGHT_VAL_TRANSLATED_CAM;
	// else if (key == KEY_S)
	//     // cam->orig.z -= ((cam->normal.z > 0) - (cam->normal.z < 0)) * WEIGHT_VAL_TRANSLATED_CAM;
	// else if (key == KEY_A)
	//     // cam->orig.x += ((cam->normal.x > 0) - (cam->normal.x < 0)) * WEIGHT_VAL_TRANSLATED_CAM;
	// else if (key == KEY_D)
	//     // cam->orig.x -= ((cam->normal.x > 0) - (cam->normal.x < 0)) * WEIGHT_VAL_TRANSLATED_CAM;
	// else if (key == KEY_SPC)
	//     // cam->orig.y += ((cam->normal.y > 0) - (cam->normal.y < 0)) * WEIGHT_VAL_TRANSLATED_CAM;
	// else if (key == KEY_C)
	//     // cam->orig.y -= ((cam->normal.y > 0) - (cam->normal.y < 0)) * WEIGHT_VAL_TRANSLATED_CAM;
	//     -> 만약에 그냥 그대로 더해주고 싶으면 이걸 사용...

	// || (is_rotate_key(key) && old != key) <- 그냥 이렇게?
	// if (cam->normal.z > 0)
	//     rot_x_axis(&cam->normal, -30 * (key == KEY_UP));
	//     else if (cam->normal.x < 0)
	//         rot_z_axis(&cam->normal, -30);
	//     else if (cam->normal.x > 0)
	//         rot_z_axis(&cam->normal, 30);
	//     else
	//         rot_x_axis(&cam->normal, 30);
	debugPrintVec("normal", &cam->normal);
	if ((key == KEY_UP) || (key == KEY_DOWN))
	{
		sign = (key == KEY_UP) - (key == KEY_DOWN);
		if (cam->normal.z > 0)
			rot_x_axis(&cam->normal, -30 * sign);
		else if (cam->normal.x < 0)
			rot_z_axis(&cam->normal, -30 * sign);
		else if (cam->normal.x > 0)
			rot_z_axis(&cam->normal, 30 * sign);
		else
			rot_x_axis(&cam->normal, 30 * sign);
	}
	else if ((key == KEY_LEFT) || (key == KEY_RIGHT))		// y 축 회전
	{
		sign = (key == KEY_LEFT) - (key == KEY_RIGHT);

		// if (cam->normal.x > 0)
		//     rot_z_axis(&cam->normal, -30 * sign);
		if (cam->normal.y < 0)
			rot_z_axis(&cam->normal, -30 * sign);
		// else if (cam->normal.y > 0)
		//     rot_z_axis(&cam->normal, 30 * sign);
		// else
		else
			rot_y_axis(&cam->normal, 30 * sign);
	}
	else if ((key == KEY_COMMA) || (key == KEY_DOT))		// z 축 회전
	{
		sign = (key == KEY_COMMA) - (key == KEY_DOT);
		printf("impossible rt rotate!\n");
		if (cam->normal.y > 0)
			rot_y_axis(&cam->normal, 30 * sign);
		else if (cam->normal.y < 0)
			rot_y_axis(&cam->normal, 30 * sign);
		else if (cam->normal.x < 0)
			rot_x_axis(&cam->normal, -30 * sign);
		else if (cam->normal.x > 0)
			rot_x_axis(&cam->normal, 30 * sign);
		else
			rot_z_axis(&cam->normal, 30 * sign);
	}
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
	// debugPrintVec("old_normal", &cam->old_normal);
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

    //
	// // || (is_rotate_key(key) && old != key) <- 그냥 이렇게?
	// if (cam->normal.z > 0)
	//     rot_x_axis(&cam->normal, -30 * (key == KEY_UP));
	// cam
	// if (key == KEY_UP)
	// {
	//     if (cam->normal.z > 0)
	//         rot_x_axis(&cam->normal, -30);
	//     else if (cam->normal.x < 0)
	//         rot_z_axis(&cam->normal, -30);
	//     else if (cam->normal.x > 0)
	//         rot_z_axis(&cam->normal, 30);
	//     else
	//         rot_x_axis(&cam->normal, 30);
    //
	// }
	// else if (key == KEY_DOWN)
	// {
	//     else
	//         rot_x_axis(&cam->normal, -30);
	// }
	// else if (key == KEY_LEFT)
	//     rot_z_axis(&cam->normal, 30);
	// else if (key == KEY_RIGHT)
	//     rot_z_axis(&cam->normal, -30);
	// else if (key == KEY_COMMA)
	//     rot_y_axis(&cam->normal, 30);
	// else if (key == KEY_DOT)
	//     rot_y_axis(&cam->normal, -30);
