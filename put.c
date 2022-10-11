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
	t_color	color;
	double	lighting_ratio;

	if (cnt != 3)
		ft_strerror("err: wrong numbers of element 'A'");
	lighting_ratio = ft_atod(argv[1]);
	color = vec_div_double(ft_atovec(argv[2], RGB), 255);
	info->ambient = vec_multi_double(color, lighting_ratio);
}

void	get_mlx_vector(t_vec *mlx_vector, t_vec normal, double *viewport, int flag)
{
	t_vec	res;
	t_vec	basis_vec;

	if ((normal.x == 0 && normal.y == 1 && normal.z == 0))
		basis_vec = vec_init(0, 0, 1);
	else if((normal.x == 0 && normal.y == -1 && normal.z == 0))
		basis_vec = vec_init(0, 0, -1);
	else
		basis_vec = vec_init(0, 1, 0);
	mlx_vector[0] = vec_multi_double(vec_unit(vec_cross(normal, basis_vec)), viewport[0]);
	mlx_vector[1] = vec_multi_double(vec_unit(vec_cross(mlx_vector[0], normal)), viewport[1]);
}

t_camera    *camera_init(t_point coor, t_vec normal, int fov)
{
    t_camera    *init;

	init = my_calloc(1, sizeof(t_camera));
	init->orig = coor;
	init->normal = normal;
	init->viewport[0] = tan((double)fov / 2 * M_PI / 180) * 2;
	init->viewport[1] = init->viewport[0] * WIN_H / WIN_W;
	// if ((normal.x == 0 && normal.y == 1 && normal.z == 0))
	// 	init->mlx_vector[0] = vec_multi_double(vec_unit(vec_cross(normal, vec_init(0, 0, 1))), init->viewport[0]);
	// else if((normal.x == 0 && normal.y == -1 && normal.z == 0))
	// 	init->mlx_vector[0] = vec_multi_double(vec_unit(vec_cross(normal, vec_init(0, 0, -1))), init->viewport[0]);
	// else
	// 	init->mlx_vector[0] = vec_multi_double(vec_unit(vec_cross(normal, vec_init(0, 1, 0))), init->viewport[0]); // RT파일에서 불가능한 회전

	init->start_point = vec_sub(vec_sub(vec_sub(init->orig, vec_div_double(init->mlx_vector[1], 2)),
                                vec_div_double(init->mlx_vector[1], 2)), vec_multi_double(vec_multi_double(normal, -1),1));
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
	t_camera	*tmp;
	t_point		coor;
	t_vec		normal;
	int			fov;

	if (cnt != 4)
		ft_strerror("err: wrong number of element 'C'");
	coor = ft_atovec(argv[1], XYZ);
	normal = ft_atovec(argv[2], UNIT);
	fov = ft_atoi(argv[3]); //잘못들어오면 exit해야함
	if (fov < 0 || fov > 180)
		ft_strerror("err: wrong camera angle");
	tmp = camera_init(coor, normal, fov);
	camera_add(&(info->camera), tmp);
}

void	put_l(t_info *info, char **argv, int cnt)
{
	t_light	*tmp;
	t_vec	origin;
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

void	put_sp(t_info *info, char **argv, int cnt)
{
	t_object	*tmp;
	t_vec		origin;
	double		radius;
	t_color		color;
	int			checker;

	if (cnt == 4 || cnt == 5)
	{
		checker = (ft_strlen(argv[0]) == 5);
		origin = ft_atovec(argv[1], XYZ);
		radius = ft_atod(argv[2]) / 2;
		color = ft_atovec(argv[3], RGB);
		tmp = object_init(SP, sphere_init(origin, radius), vec_div_double(color, 255), checker);
		tmp->bump = ft_calloc(1, sizeof(t_img));
		tmp->tex = ft_calloc(1, sizeof(t_img));
		if (cnt == 5)
		{
			tmp->bump->file_name = ft_strdup(argv[4]);
			get_bump_addr(tmp, &info->mlx);
			// get_texture_addr(tmp, &info->mlx);
		}
		obj_add(&(info->obj), tmp);
	}
	else
		ft_strerror("sp인자 개수 안맞음");
}
void	put_pl(t_info *info, char **argv, int cnt)
{
	t_object	*tmp;
	t_vec		origin;
	t_vec		normal;
	t_color		color;
	int			checker;

	if (cnt == 4 || cnt == 5)
	{
		checker = (ft_strlen(argv[0]) == 5);
		origin = ft_atovec(argv[1], XYZ);
		normal = ft_atovec(argv[2], UNIT);
		color = ft_atovec(argv[3], RGB);
		tmp = object_init(PL, plane_init(origin, normal, 0), vec_div_double(color, 255), checker);
		tmp->bump = ft_calloc(1, sizeof(t_img));
		if (cnt == 5)
		{
			tmp->bump->file_name = ft_strdup(argv[4]);
			get_bump_addr(tmp, &info->mlx);
		}
		obj_add(&(info->obj), tmp);
	}
	else
		ft_strerror("pl인자 개수 안맞음");
}

t_point	get_cap_point(t_point center, double height, t_vec normal, double sign)
{
	t_vec	ccprime;

	ccprime = vec_multi_double(vec_multi_double(normal, sign), height / 2);
	return (vec_add(center, ccprime));
}

void	put_cy(t_info *info, char **argv, int cnt)
{
	t_object	*tmp;
	t_point		center;
	t_vec		normal;
	double		format[2];
	t_color		color;
	int			checker;
	t_object	*tmp_obj;

	if (cnt == 6 || cnt == 7)
	{
		checker = (ft_strlen(argv[0]) == 5);
		center = ft_atovec(argv[1], XYZ);
		normal = ft_atovec(argv[2], UNIT);
		format[0] = ft_atod(argv[3]) / 2;
		format[1] = ft_atod(argv[4]);
		color = ft_atovec(argv[5], RGB);
		tmp = object_init(CY, cylinder_init(get_cap_point(center, format[1], normal, -1), format[0], format[1], normal), vec_div_double(color, 255), checker);
		tmp->bump = ft_calloc(1, sizeof(t_img));
		tmp->tex = ft_calloc(1, sizeof(t_img));
		if (cnt == 7)
		{
			tmp->bump->file_name = ft_strdup(argv[6]);
			get_bump_addr(tmp, &info->mlx);
			// get_texture_addr(tmp, &info->mlx);
		}
		obj_add(&(info->obj), tmp);
		tmp_obj = tmp;
		// tmp = object_init(CAP,plane_init(get_cap_point(center, format[1], normal, -1), normal, format[0]), vec_div_double(color, 255), checker);
		// // if (cnt == 7)
		// // 		tmp->bump->file_name = argv[6];
		
		// obj_add(&(info->obj), tmp);
		tmp = object_init(CAP,plane_init(get_cap_point(center, format[1], normal, 1), normal, format[0]), vec_div_double(color, 255), checker);
		if (cnt == 7)
		{
			// tmp->bump->file_name = argv[6];
			tmp->bump = tmp_obj->bump;
			// printf("%s\n", tmp->bump->file_name);
		}
		obj_add(&(info->obj), tmp);
	}
	else
		ft_strerror("cy인자 개수 안맞음");
}

void	put_cn(t_info *info, char **argv, int cnt)
{
	t_object	*tmp;
	t_point		center;
	t_vec		normal;
	double		format[2];
	t_color		color;
	int			checker;
	t_object	*tmp_obj;

	if (cnt == 6 || cnt == 7)
	{
		checker = (ft_strlen(argv[0]) == 5);
		center = ft_atovec(argv[1], XYZ);
		normal = ft_atovec(argv[2], UNIT);
		format[0] = ft_atod(argv[3]) / 2;
		format[1] = ft_atod(argv[4]);
		color = ft_atovec(argv[5], RGB);
		tmp = object_init(CN, cone_init(get_cap_point(center, format[1], normal, -1), format[0], format[1], normal), vec_div_double(color, 255), checker);
		tmp->bump = ft_calloc(1, sizeof(t_img));
		tmp->tex = ft_calloc(1, sizeof(t_img));
		if (cnt == 7)
		{
			tmp->bump->file_name = ft_strdup(argv[6]);
			get_bump_addr(tmp, &info->mlx);
		}
		obj_add(&(info->obj), tmp);
		tmp_obj = tmp;
		tmp = object_init(CAP,plane_init(get_cap_point(center, format[1], normal, -1), normal, format[0]), vec_div_double(color, 255), checker);
		if (cnt == 7)
			tmp->bump = tmp_obj->bump;
		obj_add(&(info->obj), tmp);
	}
	else
		ft_strerror("cn인자 개수 안맞음");
}

int 	check_format(char *format)
{
	if (!format)
		return (ERROR);
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
		ft_strerror("err: wrong format");
	return (ERROR);
}

void	put_info(t_info *info, char **elem_arg)
{
	const void	(*run[7])(t_info *, char **, int) = \
				{put_a, put_c, put_l, put_sp, put_pl, put_cy, put_cn};
	int			type;
	int			cnt;

	type = check_format(elem_arg[0]);
	if (type == ERROR)
		return ;
	cnt = 0;
	while (elem_arg[cnt])
		cnt++;
	run[type](info, elem_arg, cnt);
}
