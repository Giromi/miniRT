/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_key_obj_func.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesim <sesim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:43:46 by sesim             #+#    #+#             */
/*   Updated: 2022/10/26 08:09:40 by sesim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "my_func.h"
#include "rotation_func.h"
#include "mlx_key_func.h"
#include "mlx.h"
#include "minirt.h"

static void	_switch_obj(t_info *info, int key)
{
	if (key == KEY_E)
	{
		while (info->obj->next->type & CP)
			info->obj = info->obj->next;
		info->obj = info->obj->next;
	}
	else if (key == KEY_Q)
	{
		while (info->obj->prev->type & CP)
			info->obj = info->obj->prev;
		info->obj = info->obj->prev;
	}
}

static void	_rotate_obj(t_object *obj, t_camera *cam, int key)
{
	if (!is_rotate_key(key))
		return ;
	if (key == KEY_UP)
		obj_rotation(cam, &obj->elem->normal, 15.0, PITCH);
	else if (key == KEY_DOWN)
		obj_rotation(cam, &obj->elem->normal, -15.0, PITCH);
	else if (key == KEY_LEFT)
		obj_rotation(cam, &obj->elem->normal, 15.0, YAW);
	else if (key == KEY_RIGHT)
		obj_rotation(cam, &obj->elem->normal, -15.0, YAW);
	else if (key == KEY_COMMA)
		obj_rotation(cam, &obj->elem->normal, -15.0, ROLL);
	else if (key == KEY_DOT)
		obj_rotation(cam, &obj->elem->normal, 15.0, ROLL);
}

void	change_obj(t_info *info, int key)
{
	t_object	*cap;

	_switch_obj(info, key);
	translate_center(info->cam, &info->obj->elem->center, key);
	_rotate_obj(info->obj, info->cam, key);
	if (info->obj->type & (CN | CY))
	{
		cap = info->obj->next;
		translate_center(info->cam, &cap->elem->center, key);
		_rotate_obj(cap, info->cam, key);
		if (info->obj->type & CY)
		{
			cap = info->obj->next->next;
			translate_center(info->cam, &cap->elem->center, key);
			_rotate_obj(cap, info->cam, key);
		}
	}
}
