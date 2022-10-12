/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_object_utils_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesim <sesim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 21:23:01 by minsuki2          #+#    #+#             */
/*   Updated: 2022/10/12 16:37:52 by sesim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_conlinder(t_vector *vec, double *format, char **argv)
{
	vec[CENTER] = ft_atovec(argv[1], XYZ);
	vec[NORMAL] = ft_atovec(argv[2], UNIT);
	vec[COLOR] = ft_atovec(argv[5], RGB);
	vec[ALBEDO] = vec_div_double(vec[COLOR], 255);
	format[RADIUS] = ft_atod(argv[3]) / 2;
	format[HEIGHT] = ft_atod(argv[4]);
}

void	bump_init(t_mlx *mlx, t_object *new, char *argv)
{
	if (new->type & BM)
	{
		new->bump = my_calloc(1, sizeof(t_image));
			new->tex = my_calloc(1, sizeof(t_image));
			new->bump->file_name = ft_strdup(argv[4]);
			get_bump_addr(new, mlx);
			// get_texture_addr(new, mlx);
	}
}