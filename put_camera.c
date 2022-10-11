/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_camera.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsuki2 <minsuki2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 21:25:13 by minsuki2          #+#    #+#             */
/*   Updated: 2022/10/11 21:28:36 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	get_mlx_vector(t_vector *mlx_vec, t_vector cam_normal, \
															double *viewport)
{
	t_vector	basis_vec;
	t_vector	unit_mlx_vec[2];

	if ((cam_normal.x == 0 && cam_normal.y == 1 && cam_normal.z == 0))
		basis_vec = vec_init(0, 0, 1);
	else if((cam_normal.x == 0 && cam_normal.y == -1 && cam_normal.z == 0))
		basis_vec = vec_init(0, 0, -1);
	else
		basis_vec = vec_init(0, 1, 0);
	unit_mlx_vec[HORI] = vec_unit(vec_cross(cam_normal, basis_vec));
	unit_mlx_vec[VERT] = vec_unit(vec_cross(unit_mlx_vec[HORI], cam_normal));
	mlx_vec[HORI] = vec_multi_double(unit_mlx_vec[HORI], viewport[HORI]);
	mlx_vec[VERT] = vec_multi_double(unit_mlx_vec[VERT], viewport[VERT]);
}

t_camera    *camera_init(t_point coor, t_vector normal, int fov)
{
    t_camera    *init;
	t_vector	minus_half_mlx_vec[2];

    init = (t_camera *)my_calloc(1, sizeof(t_camera));
	init->orig = coor;
	init->normal = normal;
	init->viewport[W] = tan((double)fov / 2 * M_PI / 180) * 2;
	init->viewport[H] = init->viewport[W] * WIN_H / WIN_W;
	get_mlx_vector(init->mlx_vec, init->normal, init->viewport);
	minus_half_mlx_vec[HORI] = vec_div_double(init->mlx_vec[HORI], -2);
	minus_half_mlx_vec[VERT] = vec_div_double(init->mlx_vec[VERT], -2);
	init->start_point = vec_multi_add(minus_half_mlx_vec[HORI], \
											minus_half_mlx_vec[VERT], normal);
    return (init);
}

void    camera_add(t_camera **list, t_camera *new)
{
    t_camera    *cur;

    if (list == NULL)
        return ;
    if (*list == NULL)
    {
        *list = new;
		(*list)->next = *list;
        return ;
    }
    cur = *list;
    while (cur->next && cur->next != *list)
        cur = cur->next;
    cur->next = new;
	new->next = *list;
}

void	put_c(t_info *info, char **argv, int cnt)
{
	t_point	coor;
	t_vector	normal;
	int		fov;
	t_camera *tmp;

	if (cnt != 4)
		ft_strerror("err: wrong 'camera' element arguments");
	coor = ft_atovec(argv[1], XYZ);
	normal = ft_atovec(argv[2], UNIT);
	fov = ft_atoi(argv[3]); //잘못들어오면 exit해야함
	if (fov < 0 || fov > 180)
		ft_strerror("err: wrong camera angle");
	tmp = camera_init(coor, normal, fov);
	camera_add(&(info->camera), tmp);
}
