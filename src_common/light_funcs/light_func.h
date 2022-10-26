/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_func.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesim <sesim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 09:09:41 by sesim             #+#    #+#             */
/*   Updated: 2022/10/26 09:16:09 by sesim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_FUNC_H
# define LIGHT_FUNC_H

/***** ray funcs *****/
int			is_ray_hit(t_object *obj, t_ray *ray, t_moment *spot);
int			ray_at_plane(t_object *obj, t_ray *ray, t_moment *spot);
int			ray_at_cap(t_object *obj, t_ray *ray, t_moment *spot);
int			ray_at_sphere(t_object *obj, t_ray *ray, t_moment *spot);
int			ray_at_conlinder(t_object *obj, t_ray *ray, t_moment *spot, \
					void (*get_abc)(double *term, t_ray *ray, t_model *cy));
int			ray_at_cap(t_object *obj, t_ray *ray, t_moment *spot);
t_point		get_hit_point(t_ray *ray, double t);

/***** ray utils funcs 1 *****/
void		get_spot_e_vector(t_moment *spot, t_vector *obj_n, t_vector std_n);
void		get_bump_rgb(t_moment *spot, t_object *obj);
int			is_t_in_range(t_moment *spot, double root);
int			is_h_in_range(t_model *cny, t_ray *ray, t_vector *coor, \
															t_function *func);

/***** light funcs *****/
t_vector	phong_lighting(t_info *info, t_record *rec);
int			get_diffuse(t_object *obj, t_record *rec, \
						t_light *cur_light, t_vector *light);
void		get_specular(t_record *rec, t_light *cur_light, t_vector *light);

/*****  cal root funcs  *****/
void		get_sp_abc(double *term, t_ray *ray, t_model *sp);
void		get_cy_abc(double *term, t_ray *ray, t_model *cy);
void		get_cn_abc(double *term, t_ray *ray, t_model *cy);
int			get_2d_root(t_function	*func, t_ray *ray, t_model *elem, \
						void (*get_abc)(double *, t_ray *, t_model *));

#endif