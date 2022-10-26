/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesim <sesim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 11:10:12 by sesim             #+#    #+#             */
/*   Updated: 2022/10/26 08:14:11 by sesim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "my_func.h"
#include "rotation_func.h"
#include "mlx_key_func.h"

static void	_set_quaternion_q_comp(t_q_comp *q_set, t_vector *axis, \
									const double *rad)
{
	q_set[ORIGIN_Q].w = rad[COS];
	q_set[ORIGIN_Q].i = axis->x * rad[SIN];
	q_set[ORIGIN_Q].j = axis->y * rad[SIN];
	q_set[ORIGIN_Q].k = axis->z * rad[SIN];
	q_set[CONJUGATE_Q].w = rad[COS];
	q_set[CONJUGATE_Q].i = -axis->x * rad[SIN];
	q_set[CONJUGATE_Q].j = -axis->y * rad[SIN];
	q_set[CONJUGATE_Q].k = -axis->z * rad[SIN];
}

static void	_set_quaternion_axis(t_q_comp *q_comp, t_camera *cam, \
									const double *rad, int flag)
{
	if (flag & PITCH)
		_set_quaternion_q_comp(q_comp, &cam->vec[T], rad);
	else if (flag & YAW)
		_set_quaternion_q_comp(q_comp, &cam->vec[B], rad);
	else if (flag & ROLL)
		_set_quaternion_q_comp(q_comp, &cam->vec[N], rad);
}

void	cam_rotation(t_camera *cam, t_vector *vec, double angle, int flag)
{
	t_q_comp		q_comp[2];
	const double	rad[2] = {cos(angle * M_PI / 360), sin(angle * M_PI / 360)};

	_set_quaternion_axis(q_comp, cam, rad, flag);
	if (flag & (YAW | ROLL))
		cal_quaternion(&vec[T], q_comp);
	if (flag & (ROLL | PITCH))
		cal_quaternion(&vec[B], q_comp);
	if (flag & (PITCH | YAW))
		cal_quaternion(&vec[N], q_comp);
}

void	obj_rotation(t_camera *cam, t_vector *vec, double angle, int flag)
{
	t_q_comp		q_comp[2];
	const double	rad[2] = {cos(angle * M_PI / 360), sin(angle * M_PI / 360)};

	_set_quaternion_axis(q_comp, cam, rad, flag);
	cal_quaternion(vec, q_comp);
}
