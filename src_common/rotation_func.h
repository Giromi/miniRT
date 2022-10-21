/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_func.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesim <sesim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 11:38:54 by sesim             #+#    #+#             */
/*   Updated: 2022/10/21 16:12:14 by sesim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROTATION_FUNC_H
# define ROTATION_FUNC_H

# include "minirt.h"

# define ROT_ANGLE 15

enum e_quaternoin_elem
{
	I	=	1,
	J,
	K
};

enum e_rotation_axis
{
	PITCH,
	YAW,
	ROLL
};

void	q_rotation(t_camera *cam, double angle, int flag);

#endif