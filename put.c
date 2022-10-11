#include "minirt.h"

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

void    light_add(t_light **list, t_light *new)
{
    t_light    *cur;

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

void	put_a(t_info *info, char **argv, int cnt)
{
	double	brightness;
	t_color	color;

	if (cnt != 3)
		ft_strerror("err: wrong 'ambient' element arguments");
	brightness = ft_atod(argv[1]);
	color = vec_div_double(ft_atovec(argv[2], RGB), 255);
	info->ambient = vec_multi_double(color, brightness);
}


t_point	get_cap_point(t_point center, double height, t_vector normal, double sign)
{
	t_vector	ccprime;

	ccprime = vec_multi_double(vec_multi_double(normal, sign), height / 2);
	return (vec_add(center, ccprime));
}


void	put_l(t_info *info, char **argv, int cnt)
{
	t_light	*tmp;
	t_vector	origin;
	double	brightness;
	t_color	color;

	if (cnt != 4)
		ft_strerror("l인자 개수 안맞음");
	origin = ft_atovec(argv[1], XYZ);
	brightness = ft_atod(argv[2]);
	color = vec_div_double(ft_atovec(argv[3], RGB), 255);
	tmp = light_init(origin, color, brightness); // 더미 albedo
	light_add(&(info->light), tmp);
}


int 	check_format(char *format)
{
	if (!format)
		return (-1);
	if (!ft_strncmp(format, "sp", 3) || !ft_strncmp(format, "sp-ch", 6))
		return (SP);
	else if (!ft_strncmp(format, "pl", 3) || !ft_strncmp(format, "pl-ch", 6))
		return (PL);
	else if (!ft_strncmp(format, "cy", 3) || !ft_strncmp(format, "cy-ch", 6))
		return (CY);
	else if (!ft_strncmp(format, "cn", 3) || !ft_strncmp(format, "cn-ch", 6))
		return (CN);
	else if (!ft_strncmp(format, "A", 2))
		return (A);
	else if (!ft_strncmp(format, "C", 2))
		return (C);
	else if (!ft_strncmp(format, "L", 2)) //맨대토리 따로 작성 L
		return (L);
	else
		ft_strerror("포맷 잘못받음");
	return (-1);
}

void	put_info(t_info *info, char **argv)
{
	static void	(*run[7])(t_info *, char **, int) \
					= {put_a, put_c, put_l, put_sp, put_pl, put_cy, put_cn};
	int			type;
	int			cnt;

	type = check_format(argv[0]);
	if (type == -1)
		return ;
	cnt = 0;
	while (argv[cnt])
		cnt++;
	run[type](info, argv, cnt);
}
