/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_func.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesim <sesim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 11:38:54 by sesim             #+#    #+#             */
/*   Updated: 2022/10/25 16:07:15 by sesim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROTATION_FUNC_H
# define ROTATION_FUNC_H

# include "minirt.h"

# define ROT_ANGLE 15

enum e_transform_options
{
	CAM		=	0,
	EDIT	=	0b1,
	OBJ		=	0b10,
	PITCH	=	0b100000000,
	YAW		=	0b1000000000,
	ROLL	=	0b10000000000
};

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