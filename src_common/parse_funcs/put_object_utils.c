/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_object_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesim <sesim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 21:23:01 by minsuki2          #+#    #+#             */
/*   Updated: 2022/10/26 13:09:44 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "minirt.h"
#include "my_func.h"
#include "put_func.h"
#include "mlx.h"

static void	_get_texture_addr(t_object *obj, t_mlx *mlx)
{
	obj->tex->img_ptr = mlx_png_file_to_image(mlx->ptr, obj->tex->file_name, \
										&obj->tex->width, &obj->tex->height);
	if (obj->tex->img_ptr)
		obj->tex->addr = mlx_get_data_addr(obj->tex->img_ptr, \
											&(obj->tex->bits_per_pixel), \
											&(obj->tex->line_length), \
											&(obj->tex->endian));
}

static void	_get_bump_addr(t_object *obj, t_mlx *mlx)
{
	obj->bump->img_ptr = mlx_png_file_to_image(mlx->ptr, obj->bump->file_name, \
										&obj->bump->width, &obj->bump->height);
	if (!obj->bump->img_ptr)
		ft_strerror("err: bump map file not found");
	obj->bump->addr = mlx_get_data_addr(obj->bump->img_ptr, \
										&(obj->bump->bits_per_pixel), \
										&(obj->bump->line_length), \
										&(obj->bump->endian));
}

void	bump_init(t_mlx *mlx, t_object *new, char **argv, int cnt)
{
	if (new->type & BM)
	{
		new->bump = my_calloc(1, sizeof(t_image));
		new->tex = my_calloc(1, sizeof(t_image));
		new->bump->file_name = ft_strdup(argv[cnt - 1]);
        new->tex->file_name = ft_strjoin("t", new->bump->file_name);
        printf("< Load information > ");
        printf("Bump map    : %s\nTexture map : %s\n", new->bump->file_name, new->tex->file_name);
		_get_bump_addr(new, mlx);
		_get_texture_addr(new, mlx);
		free(new->bump->file_name);
        free(new->tex->file_name);
	}
}

void	obj_add(t_object **list, t_object *new)
{
	t_object	*curr;

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
