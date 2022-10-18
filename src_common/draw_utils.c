/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesim <sesim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 17:53:54 by sesim             #+#    #+#             */
/*   Updated: 2022/10/18 12:19:18 by sesim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "minirt.h"

int	convert_color(t_vector clr)
{
	int	pow16[2];
	int	res;

	pow16[X] = 16 * 16 * 16 * 16;
	pow16[Y] = 16 * 16;
	res = ((int)clr.x * pow16[X]) + ((int)clr.y * pow16[Y]) + (int)(clr.z);
	return (res);
}

void	flip_normal_face(t_ray ray, t_moment *spot)
{
	if ((vec_dot(ray.dir, spot->normal) < 0) == 0)
		spot->normal = vec_mul_const(spot->normal, -1);
	return ;
}
