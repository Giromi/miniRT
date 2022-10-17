/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spread_ray.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesim <sesim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 17:49:42 by sesim             #+#    #+#             */
/*   Updated: 2022/10/17 14:08:08 by sesim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	_ray_at_obj(t_object *obj, t_ray ray, t_moment *spot)
{
	// const int	model_type = PL | SP | CY | CN | CP;
	int			hit_result;

	hit_result = FALSE;
	if (obj->type & (PL | CP))
		hit_result = ray_at_plane(obj, ray, spot);
	else if (obj->type & SP)
		hit_result = ray_at_sphere(obj, ray, spot);
	else if (obj->type & CY)
		hit_result = ray_at_cylinder(obj, ray, spot);
	else if (obj->type & CN)
		hit_result = ray_at_cone(obj, ray, spot);
	if (hit_result == FALSE)
		return (hit_result);
	spot->albedo = obj->albedo;
	return (hit_result);
}

int	is_ray_hit(t_object *obj, t_ray ray, t_moment *spot)
{
	int	hit_flag;

	hit_flag = FALSE;
	while (obj)
	{
		if (_ray_at_obj(obj, ray, spot))
		{
			hit_flag = TRUE;
			spot->tmax = spot->t;
			printf("spot->tmax = %lf\n", spot->tmax);
		}
		obj = obj->next;
	}
	return (hit_flag);
}
