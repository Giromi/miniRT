/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesim <sesim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 11:10:12 by sesim             #+#    #+#             */
/*   Updated: 2022/10/24 21:37:38 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "my_func.h"
#include "rotation_func.h"


static t_q_comp	_quarternion_mul(t_q_comp *q1, t_q_comp *q2)
{
	t_q_comp	res;

	res.w = q1->w * q2->w - q1->i * q2->i - q1->j * q2->j - q1->k * q2->k;
	res.i = q1->w * q2->i + q1->i * q2->w + q1->j * q2->k - q1->k * q2->j;
	res.j = q1->w * q2->j - q1->i * q2->k + q1->j * q2->w + q1->k * q2->i;
	res.k = q1->w * q2->k + q1->i * q2->j - q1->j * q2->i + q1->k * q2->w;
	return (res);
}

// res.w = q1->w * q2->w - q1->i * q2->i - \
//                     q1->j * q2->j - q1->k * q2->k;
//     res.i = q1->w * q2->i - q1->i * q2->w - \
//                     q1->j * q2->k - q1->k * q2->j;
//     res.j = q1->w * q2->j - q1->i * q2->k - \
//                     q1->j * q2->w - q1->k * q2->i;
//     res.k = q1->w * q2->k - q1->i * q2->j - \
//                     q1->j * q2->i - q1->k * q2->w;


static void	_set_quaternion_q_comp(t_q_comp *q_set, t_vector *axis, 
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

static void	_set_quaternion_p_comp(t_q_comp *p_set, t_vector *vec)
{
	p_set->w = 0;
	p_set->i = vec->x;
	p_set->j = vec->y;
	p_set->k = vec->z;
}

static void	_set_quaternion_to_vec(t_vector *vec, t_q_comp *p_set)
{
	vec->x = p_set->i;
	vec->y = p_set->j;
	vec->z = p_set->k;
}

static void	_cal_quaternion(t_vector *vec, t_q_comp *q_comp)
{
	t_q_comp	p_comp;
	t_q_comp	res;

	_set_quaternion_p_comp(&p_comp, vec);
	res = _quarternion_mul(&q_comp[ORIGIN_Q], &p_comp);
	// printf("res w : %lf i : %lf j : %lf k : %lf\n", res.w, res.i, res.j, res.k);
	res = _quarternion_mul(&res, &q_comp[CONJUGATE_Q]);
	_set_quaternion_to_vec(vec, &res);
	*vec = vec_unit(vec);
}


void	q_rotation(t_camera *cam, double angle, int flag)
{
	t_q_comp	q_comp[2];
	const double	rad[2] = {cos(angle * M_PI / 360), sin(angle * M_PI / 360)};

	debugPrintVec("T", &cam->vec[T]);
	debugPrintVec("B", &cam->vec[B]);
	debugPrintVec("N", &cam->vec[N]);
	if (flag == PITCH)
	{
		_set_quaternion_q_comp(q_comp, &cam->vec[T], rad);
	}
	else if (flag == YAW)
	{ _set_quaternion_q_comp(q_comp, &cam->vec[B], rad); }
	else if (flag == ROLL)
		_set_quaternion_q_comp(q_comp, &cam->vec[N], rad);
	printf("<Rotate> w : %lf i : %lf j : %lf k : %lf\n", q_comp[ORIGIN_Q].w, q_comp[ORIGIN_Q].i, q_comp[ORIGIN_Q].j, q_comp[ORIGIN_Q].k);
	printf("<Rotate> w : %lf i : %lf j : %lf k : %lf\n", q_comp[CONJUGATE_Q].w, q_comp[CONJUGATE_Q].i, q_comp[CONJUGATE_Q].j, q_comp[CONJUGATE_Q].k);
	if (flag == YAW || flag == ROLL)
	{
		// printf("cal vec[T]\n");
		_cal_quaternion(&cam->vec[T], q_comp);
	}
	if (flag == ROLL || flag == PITCH)
	{
		// printf("cal vec[B]\n");
		_cal_quaternion(&cam->vec[B], q_comp);
	}
	if (flag == PITCH || flag == YAW)
	{		
		// printf("cal vec[N]\n");
		_cal_quaternion(&cam->vec[N], q_comp);
	}
	printf("-------------------------------\n");
	printf("j • j = %lf\n", vec_dot(&cam->vec[T], &cam->vec[B]));
	printf("j • k = %lf\n", vec_dot(&cam->vec[B], &cam->vec[N]));
	printf("k • i = %lf\n", vec_dot(&cam->vec[N], &cam->vec[T]));
	// printf("tmp : %lf %lf %lf %lf\n", tmp_comp[W], tmp_comp[I], tmp_comp[J], tmp_comp.k);
	// _quaternion_to_vector(&cam->vec[N], cam->q_comp);
	// printf("%lf %lf %lf %lf\n", cam->q_comp[W], cam->q_comp[I], cam->q_comp[J], cam->q_comp.k);
	// printf("%lf %lf %lf\n", cam->vec[N].x, cam->vec[N].y, cam->vec[N].z);
}
