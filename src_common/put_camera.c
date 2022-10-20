/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_camera.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesim <sesim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 21:25:13 by minsuki2          #+#    #+#             */
/*   Updated: 2022/10/20 22:01:28 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "my_func.h"
#include "minirt.h"

void	set_mlx_vector_r_half(t_vector mlx_vec[2][2], t_vector cam_normal,
					double *viewport)
{
	t_vector	unit_mlx_vec[2];
	t_vector	cross_val[2];
	t_vector	basis_vec;

	if ((cam_normal.x == 0 && cam_normal.y == 1 && cam_normal.z == 0))
		basis_vec = vec_init(0, 0, 1);
	else if ((cam_normal.x == 0 && cam_normal.y == -1 && cam_normal.z == 0))
		basis_vec = vec_init(0, 0, -1);
	else
		basis_vec = vec_init(0, 1, 0);
	cross_val[ONE] = vec_cross(&cam_normal, &basis_vec);
	unit_mlx_vec[HORI] = vec_unit(&cross_val[ONE]);
	cross_val[TWO] = vec_cross(&unit_mlx_vec[HORI], &cam_normal);
	unit_mlx_vec[VERT] = vec_unit(&cross_val[TWO]);
	mlx_vec[VAL][HORI] = vec_mul_const(&unit_mlx_vec[HORI], viewport[HORI]);
	mlx_vec[VAL][VERT] = vec_mul_const(&unit_mlx_vec[VERT], viewport[VERT]);
	mlx_vec[R_HALF][HORI] = vec_div_const(&mlx_vec[VAL][HORI], -2);
	mlx_vec[R_HALF][VERT] = vec_div_const(&mlx_vec[VAL][VERT], -2);
}

void	set_viewport(double *viewport, int fov)
{
	viewport[W] = tan((double)fov / 2 * M_PI / 180) * 2;
	viewport[H] = viewport[W] * WIN_H / WIN_W;
}

int	veccmp(t_vector *vec, t_vector std)
{
	return (vec->x == std.x && vec->y == std.y && vec->z == std.z);
}

t_vector	is_vec_std(t_vector *vec, t_vector std)
{
	if (vec->x == std.x && vec->y == std.y && vec->z == std.z)
		return (std);
	return (vec_init(0, 0, 0));
}

static t_camera	*_camera_init(t_point coor, t_vector normal, int fov)
{
	t_camera	*init;

	init = (t_camera *)my_calloc(1, sizeof(t_camera));
	init->orig = coor;
	init->normal = normal;
	set_viewport(init->viewport, fov);
	set_mlx_vector_r_half(init->mlx_vec, init->normal, init->viewport);
	init->start_point = vec_once_add_point(init->orig, \
									&init->mlx_vec[R_HALF][HORI], \
									&init->mlx_vec[R_HALF][VERT], &normal);
	init->old_normal = is_vec_std(&init->normal, vec_init(1, 0, 0));
	init->old_normal = is_vec_std(&init->normal, vec_init(0, 1, 0));
	init->old_normal = is_vec_std(&init->normal, vec_init(0, 0, 1));
	init->old_normal = is_vec_std(&init->normal, vec_init(-1, 0, 0));
	init->old_normal = is_vec_std(&init->normal, vec_init(0, -1, 0));
	// fmax(init->normal)
	if (veccmp(&init->old_normal, vec_init(0, 0, 0)))
		init->old_normal = vec_init(0, 0, -1);
	return (init);
}

static void	_camera_add(t_camera **list, t_camera *new)
{
	t_camera	*curr;

	if (list == NULL)
		return ;
	if (*list == NULL)
	{
		*list = new;
		(*list)->next = *list;
		(*list)->prev = *list;
	}
	else
	{
		curr = *list;
		while (curr->next && curr->next != *list)
			curr = curr->next;
		curr->next = new;
		new->next = *list;
		new->prev = curr;
		(*list)->prev = new;
	}
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
	fov = ft_atoi_exit(argv[3]);
	if (fov < 0 || fov > 180)
		ft_strerror("err: wrong camera angle");
	tmp = _camera_init(coor, normal, fov);
	_camera_add(&(info->camera), tmp);
}
