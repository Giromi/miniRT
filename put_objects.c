/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_objects.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesim <sesim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 21:23:01 by minsuki2          #+#    #+#             */
/*   Updated: 2022/10/16 14:38:14 by sesim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	put_pl(t_info *info, char **argv, int cnt, int type)
{
	t_object	*new;
	t_plane		*pl;
	t_vector	vec[4];

	if (cnt < 4 || cnt > 5)
		ft_strerror("err: wrong number of arguments in 'PL'");
	else
	{
		vec[CENTER] = ft_atovec(argv[1], XYZ);
		vec[NORMAL] = ft_atovec(argv[2], UNIT);
		vec[COLOR] = ft_atovec(argv[3], RGB);
		vec[ALBEDO] = vec_div_const(vec[COLOR], 255);
		pl = pl_init(vec[CENTER], vec[NORMAL], 0);
		new = obj_init(type, vec[ALBEDO], pl);
		if (type & BM)
		{
			new->bump = my_calloc(1, sizeof(t_image));
			new->bump->file_name = ft_strdup(argv[4]);
			get_bump_addr(new, &info->mlx);
		}
		obj_add(&(info->obj), new);
	}
}

void	put_sp(t_info *info, char **argv, int cnt, int type)
{
	t_object	*new;
	t_sphere	*sp;
	t_vector	vec[3];
	double		radius;

	if (cnt < 4 || cnt > 5)
		ft_strerror("err: wrong number of arguments in 'SP'");
	else
	{
		vec[CENTER] = ft_atovec(argv[1], XYZ);
		vec[COLOR] = ft_atovec(argv[3], RGB);
		vec[ALBEDO] = vec_div_const(vec[COLOR], 255);
		radius = ft_atod(argv[2]) / 2;
		sp = sp_init(vec[CENTER], radius);
		new = obj_init(type, vec[ALBEDO], sp);
		bump_init(&info->mlx, new, argv);
		obj_add(&(info->obj), new);
	}
}

static void	put_cap(t_info *info, t_object *obj, t_vector *vec, double *format)
{
	t_object	*new;
	t_plane		*pl;
	t_point		vertex;
	const int	type = CP | (obj->type & (BM | CH));
	int			cnt;

	cnt = 1;
	if (obj->type & CY)
		cnt = 2;
	while (cnt--)
	{
		vertex = get_cap_point(vec[CENTER], vec[NORMAL], format[HEIGHT], \
								(1 + ((cnt == 1) * -2)));
		pl = pl_init(vertex, vec[NORMAL], format[RADIUS]);
		new = obj_init(type, vec[ALBEDO], pl);
		if (obj->type & BM)
			new->bump = obj->bump;
		obj_add(&(info->obj), new);
	}
}

void	put_cny(t_info *info, char **argv, int cnt, int type)
{
	t_object	*new;
	t_model		*side_pl;
	t_vector	vec[4];
	double		format[2];
	t_point		vertex;

	if (cnt < 6 || cnt > 7)
		ft_strerror("err: wrong number of arguments in 'CY'");
	else
	{
		init_conlinder(vec, format, argv);
		vertex = get_cap_point(vec[CENTER], vec[NORMAL], format[HEIGHT], -1);
		side_pl = cny_init(vertex, vec[NORMAL], format[RADIUS], format[HEIGHT]);
		new = obj_init(type, vec[ALBEDO], side_pl);
		bump_init(&info->mlx, new, argv);
		obj_add(&(info->obj), new);
		put_cap(info, new, vec, format);
	}
}

// void	put_cn(t_info *info, char **argv, int cnt, int type)
// {
// 	t_object	*new;
// 	t_point		center;
// 	t_vector		normal;
// 	double		format[2];
// 	t_color		color;
// 	int			checker;
// 	t_object	*new_obj;

// 	if (cnt < 6 || cnt > 7)
// 		ft_strerror("err: wrong number of arguments in 'CN'");
// 	else
// 	{
// 		checker = (ft_strlen(argv[0]) == 5);
// 		center = ft_atovec(argv[1], XYZ);
// 		normal = ft_atovec(argv[2], UNIT);
// 		format[0] = ft_atod(argv[3]) / 2;
// 		format[1] = ft_atod(argv[4]);
// 		color = ft_atovec(argv[5], RGB);
// 		new = obj_init(CN, cn_init(get_cap_point(center, format[1], normal, -1), format[0], format[1], normal), vec_div_const(color, 255), checker);
// 		bump_init(&info->mlx, new, argv);
// 		obj_add(&(info->obj), new);
// 		new_obj = new;
// 		new = obj_init(CP,pl_init(get_cap_point(center, format[1], normal, -1), normal, format[0]), vec_div_const(color, 255), checker);
// 		if (cnt == 7)
// 		{
// 			new->bump = new_obj->bump;
// 			// new->bump->file_name = new_obj->bump->file_name;
// 		}
// 		obj_add(&(info->obj), new);
// 	}
// }
