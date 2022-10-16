/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_camera.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesim <sesim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 21:25:13 by minsuki2          #+#    #+#             */
/*   Updated: 2022/10/16 18:11:30 by sesim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	get_mlx_vector(t_vector *mlx_vec, t_vector cam_normal,
					double *viewport)
{
	t_vector	basis_vec;
	t_vector	unit_mlx_vec[2];

	if ((cam_normal.x == 0 && cam_normal.y == 1 && cam_normal.z == 0))
		basis_vec = vec_init(0, 0, 1);
	else if ((cam_normal.x == 0 && cam_normal.y == -1 && cam_normal.z == 0))
		basis_vec = vec_init(0, 0, -1);
	else
		basis_vec = vec_init(0, 1, 0);
	unit_mlx_vec[HORI] = vec_unit(vec_cross(cam_normal, basis_vec));
	unit_mlx_vec[VERT] = vec_unit(vec_cross(unit_mlx_vec[HORI], cam_normal));
	mlx_vec[HORI] = vec_mul_const(unit_mlx_vec[HORI], viewport[HORI]);
	mlx_vec[VERT] = vec_mul_const(unit_mlx_vec[VERT], viewport[VERT]);
}

t_camera	*camera_init(t_point coor, t_vector normal, int fov)
{
	t_camera	*init;
	t_vector	minus_half_mlx_vec[2];

	init = (t_camera *)my_calloc(1, sizeof(t_camera));
	init->orig = coor;
	init->normal = normal;
	init->viewport[W] = tan((double)fov / 2 * M_PI / 180) * 2;
	init->viewport[H] = init->viewport[W] * WIN_H / WIN_W;
	get_mlx_vector(init->mlx_vec, init->normal, init->viewport);
	minus_half_mlx_vec[HORI] = vec_div_const(init->mlx_vec[HORI], -2);
	minus_half_mlx_vec[VERT] = vec_div_const(init->mlx_vec[VERT], -2);
	init->start_point = vec_once_add_point(init->orig, \
											minus_half_mlx_vec[HORI], \
											minus_half_mlx_vec[VERT], normal);
	return (init);
}

void	camera_add(t_camera **list, t_camera *new)
{
	t_camera	*spot;

	if (list == NULL)
		return ;
	if (*list == NULL)
	{
		*list = new;
		(*list)->next = *list;
		return ;
	}
	spot = *list;
	while (spot->next && spot->next != *list)
		spot = spot->next;
	spot->next = new;
	new->next = *list;
}

void	put_c(t_info *info, char **argv, int cnt, int type)
{
	t_camera	*tmp;
	t_vector	normal;
	t_point		coor;
	int			fov;

	if (cnt != 4 || type != C)
		ft_strerror("err: wrong 'camera' element arguments");
	coor = ft_atovec(argv[1], XYZ);
	normal = ft_atovec(argv[2], UNIT);
	fov = ft_atoi(argv[3]); //잘못들어오면 exit해야함
	if (fov < 0 || fov > 180)
		ft_strerror("err: wrong camera angle");
	tmp = camera_init(coor, normal, fov);
	camera_add(&(info->camera), tmp);
}
