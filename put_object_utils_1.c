/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_object_utils_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesim <sesim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 21:23:01 by minsuki2          #+#    #+#             */
/*   Updated: 2022/10/12 15:44:18 by sesim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_point	get_cap_point(t_point center, t_vector normal, double height, double sign)
{
	t_vector	ccprime;

	ccprime = vec_multi_double(vec_multi_double(normal, sign), height / 2);
	return (vec_add(center, ccprime));
}

void	get_texture_addr(t_object *obj, t_mlx *mlx)
{
	int		format[2];
	int		idx[2];
	char	*texture;

	ft_bzero(idx, sizeof(idx));
	texture = ft_strjoin("t", obj->bump->file_name);
	obj->tex->img_ptr = mlx_png_file_to_image(mlx->ptr, texture, &format[0], &format[1]);
	if (!obj->tex->img_ptr)
		ft_strerror("없는 파일임");
	obj->tex->addr = mlx_get_data_addr(obj->tex->img_ptr, \
											&(obj->tex->bits_per_pixel), \
											&(obj->tex->line_length), \
											&(obj->tex->endian));
	obj->tex->width = format[0];
	obj->tex->height = format[1];
	free(texture);
}

void	get_bump_addr(t_object *obj, t_mlx *mlx)
{
	int		format[2];
	int		idx[2];

	ft_bzero(idx, sizeof(idx));
	obj->bump->img_ptr = mlx_png_file_to_image(mlx->ptr, obj->bump->file_name, &format[0], &format[1]);
	if (!obj->bump->img_ptr)
		ft_strerror("없는 파일임");
	obj->bump->addr = mlx_get_data_addr(obj->bump->img_ptr, \
											&(obj->bump->bits_per_pixel), \
											&(obj->bump->line_length), \
											&(obj->bump->endian));
	obj->bump->width = format[0];
	obj->bump->height = format[1];
}

void    obj_add(t_object **list, t_object *new)
{
    t_object    *cur;

    if (list == NULL)
        return ;
    if (*list == NULL)
    {
        *list = new;
        return ;
    }
    cur = *list;
    while (cur->next)
        cur = cur->next;
    cur->next = new;
}
