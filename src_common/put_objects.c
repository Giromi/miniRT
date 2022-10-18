/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_objects.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesim <sesim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 21:23:01 by minsuki2          #+#    #+#             */
/*   Updated: 2022/10/18 12:19:37 by sesim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "my_func.h"
#include "minirt.h"

void	put_pl(t_info *info, char **argv, int cnt, int type)
{
	t_object	*new;
	t_plane		*pl;
	t_vector	vec[4];

	if (cnt < 4 || cnt > 6)
		ft_strerror("err: wrong number of arguments in 'PL'");
	else
	{
		vec[CENTER] = ft_atovec(argv[1], XYZ);
		vec[NORMAL] = ft_atovec(argv[2], UNIT);
		vec[COLOR] = ft_atovec(argv[3], RGB);
		vec[ALBEDO] = vec_div_const(vec[COLOR], 255);
		pl = pl_init(vec[CENTER], vec[NORMAL], 0);
		new = obj_init(type, vec[ALBEDO], pl);
		bump_init(&info->mlx, new, argv, cnt);
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
		bump_init(&info->mlx, new, argv, cnt);
		obj_add(&(info->obj), new);
	}
}

static t_point	_get_cap_point(t_point center, t_vector normal, \
								double height, double sign)
{
	t_vector	ccprime;

	ccprime = vec_mul_const(vec_mul_const(normal, sign), height / 2);
	return (vec_add(center, ccprime));
}

static void	put_cap(t_info *info, t_object *obj, t_vector *vec, double *format)
{
	t_object	*new;
	t_plane		*pl;
	const int	type = CP | (obj->type & (BM | CH));

	pl = pl_init(vec[4], vec[NORMAL], format[RADIUS]);
	new = obj_init(type, vec[ALBEDO], pl);
	if (obj->type & BM)
		new->bump = obj->bump;
	obj_add(&(info->obj), new);
	if (obj->type & CY)
	{
		vec[4] = _get_cap_point(vec[CENTER], vec[NORMAL], format[HEIGHT], 1);
		pl = pl_init(vec[4], vec[NORMAL], format[RADIUS]);
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
	t_vector	vec[5];
	double		format[2];

	if (cnt < 6 || cnt > 7)
	{
		if (type & CY)
			ft_strerror("err: wrong number of arguments in 'CY'");
		else if (type & CN)
			ft_strerror("err: wrong number of arguments in 'CN'");
	}
	else
	{
		init_conlinder(vec, format, argv);
		vec[4] = _get_cap_point(vec[CENTER], vec[NORMAL], format[HEIGHT], -1);
		side_pl = cny_init(vec[4], vec[NORMAL], format[RADIUS], format[HEIGHT]);
		new = obj_init(type, vec[ALBEDO], side_pl);
		bump_init(&info->mlx, new, argv, cnt);
		obj_add(&(info->obj), new);
		put_cap(info, new, vec, format);
	}
}
