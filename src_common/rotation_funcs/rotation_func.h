/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_func.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesim <sesim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 11:38:54 by sesim             #+#    #+#             */
/*   Updated: 2022/10/26 08:03:32 by sesim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROTATION_FUNC_H
# define ROTATION_FUNC_H

# include "minirt.h"

# define ROT_ANGLE 15

enum e_quaternoin_elem
{
	I			=	1,
	J,
	K,
	ORIGIN_Q	=	0,
	CONJUGATE_Q	=	1,
	COS			=	0,
	SIN			=	1
};

typedef struct s_q_comp
{
	double	w;
	double	i;
	double	j;
	double	k;
}	t_q_comp;

void	cam_rotation(t_camera *cam, t_vector *vec, double angle, int flag);
void	obj_rotation(t_camera *cam, t_vector *vec, double angle, int flag);
void	cal_quaternion(t_vector *vec, t_q_comp *q_comp);

#endif