#include "minirt.h"

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

void	put_l(t_info *info, char **argv, int cnt)
{
	t_light		*tmp;
	t_vector	origin;
	t_color		color;
	double		brightness;

	if (cnt != 4)
		ft_strerror("err: wrong 'light' element arguments");
	origin = ft_atovec(argv[1], XYZ);
	brightness = ft_atod(argv[2]);
	color = vec_div_double(ft_atovec(argv[3], RGB), 255);
	tmp = light_init(origin, color, brightness);	
	light_add(&(info->light), tmp);
}

static int 	_check_format(char *format, int *form_check)
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
	else if (!ft_strncmp(format, "A", 2) && ++form_check[A])
		return (A);
	else if (!ft_strncmp(format, "C", 2) && ++form_check[C])
		return (C);
	else if (!ft_strncmp(format, "L", 2) && ++form_check[L])
		return (L);
	else
		ft_strerror("err: wrong format");
	return (-1);
}

void	put_info(t_info *info, char **argv, int *form_check)
{
	static void	(*run[7])(t_info *, char **, int) \
					= {put_a, put_c, put_l, put_sp, put_pl, put_cy, put_cn};
	int			type;
	int			cnt;

	type = _check_format(argv[0], form_check);
	if (type == -1)
		return ;
	cnt = 0;
	while (argv[cnt])
		cnt++;
	run[type](info, argv, cnt);
}
