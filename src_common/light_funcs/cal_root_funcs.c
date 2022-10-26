/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cal_root_funcs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesim <sesim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 18:07:17 by sesim             #+#    #+#             */
/*   Updated: 2022/10/26 09:16:30 by sesim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "minirt.h"
#include "light_func.h"

void	get_sp_abc(double *term, t_ray *ray, t_model *sp)
{
	t_vector		w;
	const double	r_pow_2 = sp->radius * sp->radius;

	w = vec_sub(&ray->orig, &sp->center);
	term[A] = vec_len_pow(&ray->dir);
	term[B] = vec_dot(&ray->dir, &w);
	term[C] = vec_len_pow(&w) - r_pow_2;
}

void	get_cy_abc(double *term, t_ray *ray, t_model *cy)
{
	t_vector		w;
	const double	r_pow_2 = cy->radius * cy->radius;
	double			dot_val[3];
	double			dot_multiple[3];

	w = vec_sub(&ray->orig, &cy->center);
	dot_val[V_N] = vec_dot(&ray->dir, &cy->normal);
	dot_val[V_W] = vec_dot(&ray->dir, &w);
	dot_val[W_N] = vec_dot(&w, &cy->normal);
	dot_multiple[V_N] = dot_val[V_N] * dot_val[V_N];
	dot_multiple[V_W] = dot_val[V_N] * dot_val[W_N];
	dot_multiple[W_N] = dot_val[W_N] * dot_val[W_N];
	term[A] = vec_len_pow(&ray->dir) - dot_multiple[V_N];
	term[B] = dot_val[V_W] - dot_multiple[V_W];
	term[C] = vec_len_pow(&w) - dot_multiple[W_N] - r_pow_2;
}

void	get_cn_abc(double *term, t_ray *ray, t_model *cn)
{
	t_vector		w;
	const double	pow_2[2] = {cn->radius * cn->radius, \
								cn->height * cn->height};
	const double	m = pow_2[RADIUS] / pow_2[HEIGHT];
	double			dot_val[3];
	double			dot_multiple[3];

	w = vec_sub(&ray->orig, &cn->center);
	dot_val[V_N] = vec_dot(&ray->dir, &cn->normal);
	dot_val[V_W] = vec_dot(&w, &ray->dir);
	dot_val[W_N] = vec_dot(&w, &cn->normal);
	dot_multiple[V_N] = dot_val[V_N] * dot_val[V_N];
	dot_multiple[V_W] = dot_val[V_N] * dot_val[W_N];
	dot_multiple[W_N] = dot_val[W_N] * dot_val[W_N];
	term[A] = vec_len_pow(&ray->dir) - ((m + 1) * dot_multiple[V_N]);
	term[B] = dot_val[V_W] - ((m + 1) * dot_multiple[V_W]) + \
								(m * cn->height * dot_val[V_N]);
	term[C] = vec_len_pow(&w) - ((m + 1) * dot_multiple[W_N]) + \
						(2 * m * cn->height * dot_val[W_N] - pow_2[RADIUS]);
}

int	get_2d_root(t_function	*func, t_ray *ray, t_model *elem, \
				void (*get_abc)(double *, t_ray *, t_model *))
{
	double	judge;
	double	sqrt_judge;

	get_abc(func->term, ray, elem);
	judge = (func->term[B] * func->term[B]) - (func->term[A] * func->term[C]);
	if (judge < 0)
		return (ERROR);
	sqrt_judge = sqrt(judge);
	func->root[0] = (-func->term[B] - sqrt_judge) / func->term[A];
	func->root[1] = (-func->term[B] + sqrt_judge) / func->term[A];
	return (TRUE);
}
