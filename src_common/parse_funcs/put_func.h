/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_func.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesim <sesim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 08:45:05 by sesim             #+#    #+#             */
/*   Updated: 2022/10/25 12:46:56 by sesim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUT_FUNC_H
# define PUT_FUNC_H

/***** put funcs *****/
void		info_init(t_info *info, char *file);
void		info_error(int *form_check);
void		put_a(t_info *info, char **argv, int cnt, int type);
void		put_l(t_info *info, char **argv, int cnt, int type);
void		put_c(t_info *info, char **argv, int cnt, int type);
void		put_pl(t_info *info, char **argv, int cnt, int type);
void		put_sp(t_info *info, char **argv, int cnt, int tye);
void		put_cny(t_info *info, char **argv, int cnt, int type);
void		set_mlx_vector_r_half(t_vector mlx_vec[2][2], t_vector *cam_vec,
					double *viewport);

/***** init funcs *****/
t_sphere	*sp_init(t_point *center, double radius);
t_plane		*pl_init(t_point *center, t_vector *normal, double radius);
t_conlinder	*cny_init(t_point *center, t_vector *normal, \
							double radius, double height);
t_object	*obj_init(t_object_type type, t_vector *albedo, t_model *element);

#endif
