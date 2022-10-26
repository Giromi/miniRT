/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_mouse_func.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesim <sesim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 22:15:56 by minsuki2          #+#    #+#             */
/*   Updated: 2022/10/26 12:23:27 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "minirt.h"
#include "my_func.h"
#include "put_func.h"
#include "mlx.h"
#include "mlx_key_func.h"

void	mouse_event(t_info *info, int button)
{
	if (button == MOU_HEEL_DOWN && info->cam->fov < 180)
		info->cam->fov += 5;
	else if (button == MOU_HEEL_UP && info->cam->fov > 0)
		info->cam->fov -= 5;
	set_viewport(info->cam->viewport, info->cam->fov);
	set_mlx_vector_r_half(info->cam->mlx_vec, info->cam->vec, \
							info->cam->viewport);
	info->cam->start_point = vec_once_add_point(info->cam->orig, \
									&info->cam->mlx_vec[R_HALF][HORI], \
									&info->cam->mlx_vec[R_HALF][VERT], \
									&info->cam->vec[N]);
}
