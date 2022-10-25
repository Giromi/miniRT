/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_mouse_func.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesim <sesim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 22:15:56 by minsuki2          #+#    #+#             */
/*   Updated: 2022/10/25 12:31:56 by sesim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "my_func.h"
#include "minirt.h"
#include "put_func.h"
#include "mlx.h"

void	mouse_event(t_info *info, int button)
{
	printf("%d\n", info->camera->fov);
	if (button == MOU_HEEL_DOWN && info->camera->fov < 180)
		info->camera->fov += 5;
	else if (button == MOU_HEEL_UP && info->camera->fov > 0)
		info->camera->fov -= 5;
	set_viewport(info->camera->viewport, info->camera->fov);
	set_mlx_vector_r_half(info->camera->mlx_vec, info->camera->vec, info->camera->viewport);
	info->camera->start_point = vec_once_add_point(info->camera->orig, \
									&info->camera->mlx_vec[R_HALF][HORI], \
									&info->camera->mlx_vec[R_HALF][VERT], &info->camera->vec[N]);
}
