#include "minirt.h"

void    light_add(t_light **list, t_light *new)
{
    t_light    *cur;

    if (list == NULL)
        return ;
    if (*list == NULL) {
        *list = new;
        return ;
    }
    cur = *list;
    while (cur->next)
        cur = cur->next;
    cur->next = new;
}

void	put_a(t_info *info, char **argv, int cnt, int type)
{
	double	brightness;
	t_color	color;

	if (cnt != 3 || type != A)
		ft_strerror("err: wrong 'ambient' element arguments");
	brightness = ft_atod(argv[1]);
	color = vec_div_double(ft_atovec(argv[2], RGB), 255);
	info->ambient = vec_multi_double(color, brightness);
}

void	put_l(t_info *info, char **argv, int cnt, int type)
{
	t_light		*tmp;
	t_vector	origin;
	t_color		color;
	double		brightness;

	if (cnt != 4 || type != L)
		ft_strerror("err: wrong 'light' element arguments");
	origin = ft_atovec(argv[1], XYZ);
	brightness = ft_atod(argv[2]);
	color = vec_div_double(ft_atovec(argv[3], RGB), 255);
	tmp = light_init(origin, color, brightness);
	light_add(&(info->light), tmp);
}

static int 	_check_option(char *format)
{
	if (*format++ != '\0')
	{
		if (!ft_strncmp(format, "ch", 3))
			return (CH);
		else if (!ft_strncmp(format, "bm", 3))
			return (BM);
	}
	ft_strerror("err: unknown option");
}

static int 	_check_format(char *format, int *form_check)
{
	int		len;
	int		bit;
if (!format)
		return (-1);
	len = ft_strchr_idx(format, '-');
	bit = 0;
	if (!ft_strncmp(format, "A", 1) && ++form_check[A])
		bit |= A;
	else if (!ft_strncmp(format, "L", 1) && ++form_check[L])
		bit |= L;
	else if (!ft_strncmp(format, "C", 1) && ++form_check[C])
		bit |= C;
	else if (!ft_strncmp(format, "pl", len))
		bit |= PL;
	else if (!ft_strncmp(format, "sp", len))
		bit |= SP;
	else if (!ft_strncmp(format, "cy", len))
		bit |= CY;
	else if (!ft_strncmp(format, "cn", len))
		bit |= CN;
	else
		ft_strerror("err: wrong format");
	bit |= check_options(format + len);
	return (bit);
}

void	put_info(t_info *info, char **argv, int *form_check)
{
	static void	(*run[7])(t_info *, char **, int, int) \
					= {put_a, put_l, put_c, put_sp, put_pl, put_cy, put_cn};
	int			type;
	int			cnt;
	int			idx;

	type = _check_format(argv[0], form_check);
	idx = log(type & 0xFF) / log(2);
	cnt = -1;
	while (argv[++cnt])
		;
	run[idx](info, argv, cnt, type);
}
