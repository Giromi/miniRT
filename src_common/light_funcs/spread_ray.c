/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spread_ray.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesim <sesim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 17:49:42 by sesim             #+#    #+#             */
/*   Updated: 2022/10/26 09:16:58 by sesim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "minirt.h"
#include "light_func.h"

static int	_ray_at_obj(t_object *obj, t_ray *ray, t_moment *spot)
{
	int	hit_result;

	hit_result = FALSE;
	if (obj->type & PL)
		hit_result = ray_at_plane(obj, ray, spot);
	else if (obj->type & SP)
		hit_result = ray_at_sphere(obj, ray, spot);
	else if (obj->type & CY)
		hit_result = ray_at_conlinder(obj, ray, spot, get_cy_abc);
	else if (obj->type & CN)
		hit_result = ray_at_conlinder(obj, ray, spot, get_cn_abc);
	else if (obj->type & CP)
		hit_result = ray_at_cap(obj, ray, spot);
	if (hit_result == FALSE)
		return (hit_result);
	return (hit_result);
}

int	is_ray_hit(t_object *obj, t_ray *ray, t_moment *spot)
{
	t_object	*curr;
	int			hit_flag;

	hit_flag = FALSE;
	curr = obj;
	while (curr)
	{
		if (_ray_at_obj(curr, ray, spot))
		{
			hit_flag = TRUE;
			spot->checker = (curr->type & CH);
			spot->t_[MAX] = spot->t_[VAL];
		}
		curr = curr->next;
		if (curr == obj)
			break ;
	}
	return (hit_flag);
}
