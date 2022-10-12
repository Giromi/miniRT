#include "minirt.h"

static void	_light_add(t_light **list, t_light *new)
{
	t_light	*cur;

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

static t_light	*_light_init(t_vector l_origin, t_vector l_color, double br)
{
	t_light *light;

	light = my_calloc(1, sizeof(t_light));
	light->origin = l_origin;
	light->light_color = l_color;
	light->brightness = br;
	return (light);
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
	tmp = _light_init(origin, color, brightness);	
	_light_add(&(info->light), tmp);
}
