/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesim <sesim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 18:07:00 by sesim             #+#    #+#             */
/*   Updated: 2022/10/18 20:16:56 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "minirt.h"

static t_vector	_sigma_brightness(t_info *info, t_light *cur_light)
{
	t_vector	light[4];
	double		brightness;

	if (get_diffuse(info, cur_light, light) == ERROR)
		return (vec_init(0, 0, 0));
	get_specular(info, cur_light, light);
	brightness = cur_light->brightness * LUMEN;
	light[COMPUTE] = vec_add(light[DIFFUSE], light[SPECULAR]);
	return (vec_mul_const(light[COMPUTE], brightness));
}

static t_color	_checkerboard_value(t_moment spot)
{
	const int		width = 10;
	const int		height = 10;
	const double	u2 = floor(spot.u * width);
	const double	v2 = floor(spot.v * height);

	if (fmod(u2 + v2, 2.) == 0)
		return (spot.albedo);
	return (vec_init(1, 1, 1));
}

t_vector	phong_lighting(t_info *info)
{
	t_light		*lights;
	t_color		color[2];
	t_vector	vec[3];

	color[LIGHT] = vec_init(0, 0, 0);
	lights = info->light;
	while (lights)
	{
		color[LIGHT] = vec_add(color[LIGHT], _sigma_brightness(info, lights));
		lights = lights->next;
	}
	color[LIGHT] = vec_add(color[LIGHT], info->ambient);
	if (info->spot.checker)
		color[OBJECT] = _checkerboard_value((info->spot));
	else
		color[OBJECT] = info->spot.albedo;
	vec[COLOR] = vec_mul(color[LIGHT], color[OBJECT]);
	vec[ALBEDO] = vec_min(vec[COLOR], vec_init(1, 1, 1));
	vec[LIGHT] = vec_mul_const(vec[ALBEDO], 255);
	return (vec[LIGHT]);
}
