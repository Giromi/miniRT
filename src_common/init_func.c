/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesim <sesim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 18:03:38 by sesim             #+#    #+#             */
/*   Updated: 2022/10/19 14:37:34 by sesim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "my_func.h"
#include "minirt.h"

t_sphere	*sp_init(t_point center, double radius)
{
	t_sphere	*init;

	init = my_calloc(1, sizeof(t_conlinder));
	init->center = center;
	init->radius = radius;
	return (init);
}

t_plane	*pl_init(t_point center, t_vector normal, double radius)
{
	t_plane	*init;

	init = my_calloc(1, sizeof(t_conlinder));
	init->center = center;
	init->normal = normal;
	init->radius = radius;
	return (init);
}

void	init_conlinder(t_vector *vec, double *format, char **argv)
{
	vec[CENTER] = ft_atovec(argv[1], XYZ);
	vec[NORMAL] = ft_atovec(argv[2], UNIT);
	vec[COLOR] = ft_atovec(argv[5], RGB);
	vec[ALBEDO] = vec_div_const(&vec[COLOR], 255);
	format[RADIUS] = ft_atod(argv[3]) / 2;
	format[HEIGHT] = ft_atod(argv[4]);
}

t_conlinder	*cny_init(t_point center, t_vector normal,
						double radius, double height)
{
	t_conlinder	*init;

	init = my_calloc(1, sizeof(t_conlinder));
	init->center = center;
	init->radius = radius;
	init->height = height;
	init->normal = normal;
	return (init);
}

t_object	*obj_init(t_object_type type, t_vector albedo,
						t_model *element)
{
	t_object	*new;

	new = my_calloc(1, sizeof(t_object));
	new->type = type;
	new->elem = element;
	new->albedo = albedo;
	return (new);
}
