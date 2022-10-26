/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_func.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesim <sesim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 09:19:53 by sesim             #+#    #+#             */
/*   Updated: 2022/10/26 09:20:32 by sesim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_FUNC_H
# define DRAW_FUNC_H

/***** draw funcs *****/
void		my_mlx_pixel_put(t_image *img, int x, int y, t_color color);
t_color		cur_point_color(t_info *info, t_record *rec);
void		set_ray_vec(t_ray *ray, t_camera *cam, double *vdx);
void		flip_normal_face(t_ray *ray, t_moment *spot);

/***** draw utils funcs *****/
t_vector	convert_color_to_normal(int color);
int			convert_color(t_vector *clr);

#endif
