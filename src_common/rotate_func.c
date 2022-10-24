/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesim <sesim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 11:10:12 by sesim             #+#    #+#             */
/*   Updated: 2022/10/24 18:39:34 by sesim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "my_func.h"
#include "rotation_func.h"

static t_q_comp	_quarternion_mul(t_q_comp *q1, t_q_comp *q2)
{
	t_q_comp	res;

	res.w = q1->w * q2->w - q1->i * q2->i - \
					q1->j * q2->j - q1->k * q2->k;
	res.i = q1->w * q2->i - q1->i * q2->w - \
					q1->j * q2->k - q1->k * q2->j;
	res.j = q1->w * q2->j - q1->i * q2->k - \
					q1->j * q2->w - q1->k * q2->i;
	res.k = q1->w * q2->k - q1->i * q2->j - \
					q1->j * q2->i - q1->k * q2->w;	
	return (res);
}

static void	_set_quaternion_q_comp(t_q_comp *q_set, t_vector *axis, double *rad)
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

static void	_set_quaternion_p_comp(t_q_comp *p_set, t_vector *vec)
{
	p_set->w = 0;
	p_set->i = vec->x;
	p_set->j = vec->y;
	p_set->k = vec->z;
}

static void	_set_quaternion_to_vec(t_q_comp *p_set, t_vector *vec)
{
	vec->x = p_set->i;
	vec->y = p_set->j;
	vec->z = p_set->k;
}

static void	_cal_quaternion(t_q_comp *q_comp, t_vector *vec)
{
	t_q_comp	p_comp;
	t_q_comp	res;

	_set_quaternion_p_comp(&p_comp, vec);
	res = _quarternion_mul(&q_comp[ORIGIN_Q], &p_comp);
	res = _quarternion_mul(&res, &q_comp[CONJUGATE_Q]);
	_set_quaternion_to_vec(&res, vec);
}


void	q_rotation(t_camera *cam, double angle, int flag)
{
	t_q_comp	q_comp[2];
	double	rad[2];


	rad[0] = cos(angle * M_PI / 360);
	rad[1] = sin(angle * M_PI / 360);
	if (flag == PITCH)
		_set_quaternion_q_comp(q_comp, &cam->vec[T], rad);
	else if (flag == YAW)
		_set_quaternion_q_comp(q_comp, &cam->vec[B], rad);
	else if (flag == ROLL)
		_set_quaternion_q_comp(q_comp, &cam->vec[N], rad);
	if (flag == YAW || flag == ROLL)
		_cal_quaternion(q_comp, &cam->vec[T]);
	else if (flag == PITCH || flag == ROLL)
		_cal_quaternion(q_comp, &cam->vec[B]);
	else if (flag == PITCH || flag == YAW)
		_cal_quaternion(q_comp, &cam->vec[N]);
	// printf("tmp : %lf %lf %lf %lf\n", tmp_comp[W], tmp_comp[I], tmp_comp[J], tmp_comp.k);
	// _quaternion_to_vector(&cam->vec[N], cam->q_comp);
	// printf("%lf %lf %lf %lf\n", cam->q_comp[W], cam->q_comp[I], cam->q_comp[J], cam->q_comp.k);
	// printf("%lf %lf %lf\n", cam->vec[N].x, cam->vec[N].y, cam->vec[N].z);
}
