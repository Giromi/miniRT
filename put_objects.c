/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_objects.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesim <sesim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 21:23:01 by minsuki2          #+#    #+#             */
/*   Updated: 2022/10/12 12:03:35 by sesim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	put_pl(t_info *info, char **argv, int cnt)
{
	t_object	*new;
	t_plane		*plane;
	t_vector	vec[4];
	int			checker;

	if (cnt == 4 || cnt == 5)
	{
		checker = (ft_strlen(argv[0]) == 5);
		vec[CENTER] = ft_atovec(argv[1], XYZ);
		vec[NORMAL] = ft_atovec(argv[2], UNIT);
		vec[COLOR] = ft_atovec(argv[3], RGB);
		vec[ALBEDO] = vec_div_double(vec[COLOR], 255);
		plane = plane_init(vec[CENTER], vec[NORMAL], 0);
		new = object_init(PL, vec[ALBEDO], plane, checker);
		if (cnt == 5)
		{
			new->bump = my_calloc(1, sizeof(t_image));
			new->bump->file_name = ft_strdup(argv[4]);
			get_bump_addr(new, &info->mlx);
		}
		obj_add(&(info->obj), new);
	}
	else
		ft_strerror("err: wrong number of 'PL'");
}

void	put_sp(t_info *info, char **argv, int cnt)
{
	t_object	*tmp;
	t_vector		origin;
	double		radius;
	t_color		color;
	int			checker;

	if (cnt == 4 || cnt == 5)
	{
		checker = (ft_strlen(argv[0]) == 5);
		origin = ft_atovec(argv[1], XYZ);
		radius = ft_atod(argv[2]) / 2;
		color = ft_atovec(argv[3], RGB);
		tmp = object_init(SP, sphere_init(origin, radius), vec_div_double(color, 255), checker);
		tmp->bump = ft_calloc(1, sizeof(t_image));
		tmp->tex = ft_calloc(1, sizeof(t_image));
		if (cnt == 5)
		{
			tmp->bump->file_name = ft_strdup(argv[4]);
			get_bump_addr(tmp, &info->mlx);
			// get_texture_addr(tmp, &info->mlx);
		}
		obj_add(&(info->obj), tmp);
	}
	else
		ft_strerror("sp인자 개수 안맞음");
}


void	put_cy(t_info *info, char **argv, int cnt)
{
	t_object	*tmp;
	t_point		center;
	t_vector		normal;
	double		format[2];
	t_color		color;
	int			checker;
	t_object	*tmp_obj;

	if (cnt == 6 || cnt == 7)
	{
		checker = (ft_strlen(argv[0]) == 5);
		center = ft_atovec(argv[1], XYZ);
		normal = ft_atovec(argv[2], UNIT);
		format[0] = ft_atod(argv[3]) / 2;
		format[1] = ft_atod(argv[4]);
		color = ft_atovec(argv[5], RGB);
		tmp = object_init(CY, cylinder_init(get_cap_point(center, format[1], normal, -1), format[0], format[1], normal), vec_div_double(color, 255), checker);
		tmp->bump = ft_calloc(1, sizeof(t_image));
		tmp->tex = ft_calloc(1, sizeof(t_image));
		if (cnt == 7)
		{
			tmp->bump->file_name = ft_strdup(argv[6]);
			get_bump_addr(tmp, &info->mlx);
			// get_texture_addr(tmp, &info->mlx);
		}
		obj_add(&(info->obj), tmp);
		tmp_obj = tmp;
		tmp = object_init(CAP,plane_init(get_cap_point(center, normal, format[1], 1), normal, format[0]), vec_div_double(color, 255), checker);
		if (cnt == 7)
			tmp->bump = tmp_obj->bump;
		obj_add(&(info->obj), tmp);
		// tmp = object_init(CAP,plane_init(get_cap_point(center, format[1], normal, -1), normal, format[0]), vec_div_double(color, 255), checker);
		// // if (cnt == 7)
		// // 		tmp->bump->file_name = argv[6];

		// obj_add(&(info->obj), tmp);
	}
	else
		ft_strerror("cy인자 개수 안맞음");
}

void	put_cn(t_info *info, char **argv, int cnt)
{
	t_object	*tmp;
	t_point		center;
	t_vector		normal;
	double		format[2];
	t_color		color;
	int			checker;
	t_object	*tmp_obj;

	if (cnt == 6 || cnt == 7)
	{
		checker = (ft_strlen(argv[0]) == 5);
		center = ft_atovec(argv[1], XYZ);
		normal = ft_atovec(argv[2], UNIT);
		format[0] = ft_atod(argv[3]) / 2;
		format[1] = ft_atod(argv[4]);
		color = ft_atovec(argv[5], RGB);
		tmp = object_init(CN, cone_init(get_cap_point(center, format[1], normal, -1), format[0], format[1], normal), vec_div_double(color, 255), checker);
		tmp->bump = ft_calloc(1, sizeof(t_image));
		tmp->tex = ft_calloc(1, sizeof(t_image));
		if (cnt == 7)
		{
			tmp->bump->file_name = ft_strdup(argv[6]);
			get_bump_addr(tmp, &info->mlx);
		}
		obj_add(&(info->obj), tmp);
		tmp_obj = tmp;
		tmp = object_init(CAP,plane_init(get_cap_point(center, format[1], normal, -1), normal, format[0]), vec_div_double(color, 255), checker);
		if (cnt == 7)
		{
			tmp->bump = tmp_obj->bump;
			// tmp->bump->file_name = tmp_obj->bump->file_name;
		}
		obj_add(&(info->obj), tmp);
	}
	else
		ft_strerror("cn인자 개수 안맞음");
}
