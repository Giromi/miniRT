/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_key_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesim <sesim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 15:34:56 by sesim             #+#    #+#             */
/*   Updated: 2022/10/26 12:34:14 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "minirt.h"
#include "my_func.h"
#include "rotation_func.h"
#include "mlx.h"
#include "mlx_key_func.h"

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

int	is_view_key(int key)
{
	return (key == 18 || key == 19 || key == 20 || key == 29);
}

void	translate_center(t_camera *cam, t_point *center, int key)
{
	t_vector	move;

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
	*center = vec_add(center, &move);
}

void	key_event(t_info *info, int key)
{
	if (info->status & ANTI)
		info->status &= ~ANTI;
	if ((key == KEY_O) && (!(info->status & ANTI)))
		info->status ^= EDIT;
	else if (key == KEY_P)
		info->status ^= OBJ;
	else if (key == KEY_I)
		info->status ^= ANTI;
	if (info->status & OBJ)
		change_obj(info, key);
	else
		change_cam(info, key);
}
