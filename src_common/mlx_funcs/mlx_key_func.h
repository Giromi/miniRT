/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_key_func.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesim <sesim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 08:01:41 by sesim             #+#    #+#             */
/*   Updated: 2022/10/26 12:29:03 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_KEY_FUNC_H
# define MLX_KEY_FUNC_H

enum e_transform_options
{
	CAM		=	0,
	OBJ		=	0b1,
	EDIT	=	0b10,
	ANTI	=	0b100,
	PITCH	=	0b100000000,
	YAW		=	0b1000000000,
	ROLL	=	0b10000000000
};

/*****  mlx funcs  *****/
void		set_viewport(double *viewport, int fov);
int			key_compatible_param(int keycode, void *param);
int			mouse_compatible_param(int x, int y, int button, void *param);
int			exit_compatible_param(void *param);
void		key_event(t_info *info, int key);
void		translate_center(t_camera *cam, t_point *center, int key);
void		mouse_event(t_info *info, int button);
void		change_cam(t_info *info, int key);
void		change_obj(t_info *info, int key);
int			is_translate_key(int key);
int			is_rotate_key(int key);
int			is_view_key(int key);

#endif
