/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesim <sesim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 11:10:12 by sesim             #+#    #+#             */
/*   Updated: 2022/10/24 13:56:18 by sesim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "my_func.h"
#include "rotation_func.h"

// static double	_diag_cal_1(double *a, double *b)
// {
// 	return (1 - 2 * ((*a * *a) + (*b * *b)));
// }

// static double	_diag_cal_2(double w, double *a, double *b, double *c)
// {
// 	return (2  * ((*b * *c) + (w * *a)));
// }

// static void	_quaternion_to_vector(t_vector *n, double *rot_comp)
// {
// 	t_matrix	rot_mat[3];

// 	rot_mat[0].x = _diag_cal_1(&rot_comp[J], &rot_comp[K]);
// 	rot_mat[1].y = _diag_cal_1(&rot_comp[I], &rot_comp[K]);
// 	rot_mat[2].z = _diag_cal_1(&rot_comp[I], &rot_comp[J]);
// 	rot_mat[0].z = _diag_cal_2(rot_comp[W], &rot_comp[J], \
// 								&rot_comp[I], &rot_comp[K]);
// 	rot_mat[1].x = _diag_cal_2(rot_comp[W], &rot_comp[K], \
// 								&rot_comp[I], &rot_comp[J]);
// 	rot_mat[2].y = _diag_cal_2(rot_comp[W], &rot_comp[I], \
// 								&rot_comp[J], &rot_comp[K]);
// 	rot_mat[0].y = _diag_cal_2(-rot_comp[W], &rot_comp[K], \
// 								&rot_comp[I], &rot_comp[J]);
// 	rot_mat[1].z = _diag_cal_2(-rot_comp[W], &rot_comp[I], \
// 								&rot_comp[J], &rot_comp[K]);
// 	rot_mat[2].x = _diag_cal_2(-rot_comp[W], &rot_comp[J], \
// 								&rot_comp[I], &rot_comp[K]);
// 	*n = vec_mul_matrix(rot_mat, n);
// }

static void _quarternion_mul(double *q_comp, double *tmp_comp, \
								double *rad, int flag)
{
	if (flag == PITCH)
	{
		q_comp[W] = rad[0] * tmp_comp[W] - rad[1] * tmp_comp[I];
		q_comp[I] = rad[0] * tmp_comp[I] + rad[1] * tmp_comp[W];
		q_comp[J] = rad[0] * tmp_comp[J] - rad[1] * tmp_comp[K];
		q_comp[K] = rad[0] * tmp_comp[K] + rad[1] * tmp_comp[J];
	}
	else if (flag == YAW)
	{
		q_comp[W] = rad[0] * tmp_comp[W] - rad[1] * tmp_comp[J];
		q_comp[I] = rad[0] * tmp_comp[I] + rad[1] * tmp_comp[K];
		q_comp[J] = rad[0] * tmp_comp[J] + rad[1] * tmp_comp[W];
		q_comp[K] = rad[0] * tmp_comp[K] - rad[1] * tmp_comp[I];
	}
	else if (flag == ROLL)
	{
		q_comp[W] = rad[0] * tmp_comp[W] - rad[1] * tmp_comp[K];
		q_comp[I] = rad[0] * tmp_comp[I] - rad[1] * tmp_comp[J];
		q_comp[J] = rad[0] * tmp_comp[J] + rad[1] * tmp_comp[I];
		q_comp[K] = rad[0] * tmp_comp[K] + rad[1] * tmp_comp[W];
	}
}

void	q_rotation(t_camera *cam, double angle, int flag)
{
	double	tmp_comp[4];
	double	rad[2];

	rad[0] = cos(angle * M_PI / 360);
	rad[1] = sin(angle * M_PI / 360);
	// tmp_comp[W] = cam->q_comp[W];
	// tmp_comp[I] = cam->q_comp[I];
	// tmp_comp[J] = cam->q_comp[J];
	// tmp_comp[K] = cam->q_comp[K];
	tmp_comp[W] = 0;
	tmp_comp[I] = cam->normal.x;
	tmp_comp[J] = cam->normal.y;
	tmp_comp[K] = cam->normal.z;
	
	printf("tmp : %lf %lf %lf %lf\n", tmp_comp[W], tmp_comp[I], tmp_comp[J], tmp_comp[K]);
	_quarternion_mul(cam->q_comp, tmp_comp, rad, flag);
	cam->normal.x = cam->q_comp[I];
	cam->normal.y = cam->q_comp[J];
	cam->normal.z = cam->q_comp[K];
	// _quaternion_to_vector(&cam->normal, cam->q_comp);
	printf("%lf %lf %lf %lf\n", cam->q_comp[W], cam->q_comp[I], cam->q_comp[J], cam->q_comp[K]);
	// printf("%lf %lf %lf\n", cam->normal.x, cam->normal.y, cam->normal.z);
}
