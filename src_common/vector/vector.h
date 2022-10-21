/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesim <sesim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 21:10:46 by minsuki2          #+#    #+#             */
/*   Updated: 2022/10/21 15:44:17 by sesim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include "my_func.h"

enum e_coor_idx
{
	X	=	0,
	Y	=	1,
	Z	=	2
};

typedef struct s_vec
{
	double	x;
	double	y;
	double	z;
}	t_vector;

typedef t_vector	t_color;
typedef t_vector	t_point;
typedef t_vector	t_matrix;

/***** vector funcs *****/
t_vector	vec_once_add_point(t_point o, t_vector *a, \
								t_vector *b, t_vector *c);
t_vector	vec_mul_const(t_vector *u, double n);
t_vector	vec_mul_matrix(t_matrix *matrix, t_vector *n);
t_vector	vec_div_const(t_vector *u, double n);
t_vector	vec_cross(t_vector *u, t_vector *v);
t_vector	vec_init(double x, double y, double z);
t_vector	vec_unit(t_vector *u);
t_vector	vec_min(t_vector cmp_vec, t_vector standard);
t_vector	vec_add(t_vector *u, t_vector *v);
t_vector	vec_sub(t_vector *u, t_vector *v);
t_vector	vec_mul(t_vector *u, t_vector *v);
t_vector	vec_div(t_vector *u, t_vector *v);
double		vec_dot(t_vector *u, t_vector *v);
double		vec_len(t_vector *u);
double		vec_len_pow(t_vector *u);

#endif
