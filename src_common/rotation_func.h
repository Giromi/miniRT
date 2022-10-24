/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_func.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesim <sesim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 11:38:54 by sesim             #+#    #+#             */
/*   Updated: 2022/10/24 18:39:04 by sesim            ###   ########.fr       */
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

enum e_rotation_axis
{
	PITCH,
	YAW,
	ROLL
};

typedef struct s_q_comp
{
	double	w;
	double	i;
	double	j;
	double	k;
}	t_q_comp;

void	q_rotation(t_camera *cam, double angle, int flag);

#endif