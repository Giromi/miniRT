/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_func_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesim <sesim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:01:47 by sesim             #+#    #+#             */
/*   Updated: 2022/10/25 12:43:09 by sesim            ###   ########.fr       */
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

void	cal_quaternion(t_vector *vec, t_q_comp *q_comp)
{
	t_q_comp	p_comp;
	t_q_comp	res;

	_set_quaternion_p_comp(&p_comp, vec);
	res = _quarternion_mul(&q_comp[ORIGIN_Q], &p_comp);
	res = _quarternion_mul(&res, &q_comp[CONJUGATE_Q]);
	_set_quaternion_to_vec(vec, &res);
	*vec = vec_unit(vec);
}