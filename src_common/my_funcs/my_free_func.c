/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_free_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesim <sesim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 18:07:41 by sesim             #+#    #+#             */
/*   Updated: 2022/10/26 13:09:13 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "minirt.h"
#include "my_func.h"
#include "mlx.h"

void	split_free(char **split)
{
	int		i;

	i = -1;
	while (split[++i])
		free(split[i]);
	free(split);
	split = 0;
}

static void	_lst_cam_free(t_camera *cur)
{
	t_camera	*tmp;

	cur->prev->next = NULL;
	while (cur)
	{
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
}

static void	_lst_light_free(t_light *cur)
{
	t_light	*tmp;

	while (cur)
	{
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
}

static void	_lst_obj_free(t_object *cur, t_mlx *mlx)
{
	t_object	*tmp;

	cur->prev->next = NULL;
	while (cur)
	{
		tmp = cur->next;
		if (!(cur->type & CP) && cur->bump)
		{
            if (cur->bump->img_ptr)
                mlx_destroy_image(mlx->ptr, cur->bump->img_ptr);
			free(cur->bump);
		}
		if (!(cur->type & CP) && cur->tex)
		{
            if (cur->tex->img_ptr)
                mlx_destroy_image(mlx->ptr, cur->tex->img_ptr);
			free(cur->tex);
		}
		free(cur->elem);
		free(cur);
		cur = tmp;
	}
}

void	info_free(t_info *info, t_mlx *mlx)
{
	_lst_cam_free(info->cam);
	_lst_light_free(info->light);
	_lst_obj_free(info->obj, mlx);
}
