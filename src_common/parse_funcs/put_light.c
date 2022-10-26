/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_light.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesim <sesim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 18:15:05 by sesim             #+#    #+#             */
/*   Updated: 2022/10/26 12:21:50 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "minirt.h"
#include "my_func.h"
#include "put_func.h"

static void	_light_add(t_light **list, t_light *new)
{
	t_light	*spot;

	if (list == NULL)
		return ;
	if (*list == NULL)
	{
		*list = new;
		return ;
	}
	spot = *list;
	while (spot->next)
		spot = spot->next;
	spot->next = new;
}

static t_light	*_light_init(t_vector *l_origin, t_vector *l_color, double br)
{
	t_light	*light;

	light = my_calloc(1, sizeof(t_light));
	light->origin = *l_origin;
	light->light_color = *l_color;
	light->brightness = br;
	return (light);
}

void	put_a(t_info *info, char **argv, int cnt, int type)
{
	t_color	albedo;
	t_color	color;
	double	brightness;

	if (cnt != 3 || type != A)
		ft_strerror("err: wrong 'ambient' element arguments");
	brightness = ft_atod(argv[1]);
	color = ft_atovec(argv[2], RGB);
	albedo = vec_div_const(&color, 255);
	info->ambient = vec_mul_const(&albedo, brightness);
}

void	put_l(t_info *info, char **argv, int cnt, int type)
{
	t_light		*tmp;
	t_vector	origin;
	t_color		albedo;
	t_color		color;
	double		brightness;

	if (cnt != 4 || type != L)
		ft_strerror("err: wrong 'light' element arguments");
	origin = ft_atovec(argv[1], XYZ);
	brightness = ft_atod(argv[2]);
	color = ft_atovec(argv[3], RGB);
	albedo = vec_div_const(&color, 255);
	tmp = _light_init(&origin, &albedo, brightness);
	_light_add(&(info->light), tmp);
}
