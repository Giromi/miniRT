#include "minirt.h"

<<<<<<< HEAD
t_vector convert_int_to_rgb(int color)
=======
t_ray	ray_init(t_point orig, t_vector dir)
{
	t_ray init;

	init.orig = orig;
	init.dir = vec_unit(dir);
	return (init);
}

t_vector	convert_int_to_rgb(int	color)
>>>>>>> 06bef7fc0e97a502a9c95895049ceca6fdf38000
{
	t_vector res;

	res.x = color >> 16 & 0xFF;
	res.y = color >> 8 & 0xFF;
	res.z = color & 0xFF;
	return (res);
}

t_vector tex_rgb(t_object *obj, t_hit_record *rec)
{
	int x;
	int y;
	t_vector tmp;

	x = (int)(rec->u * obj->tex->width);
	y = (int)(rec->v * obj->tex->height);
	tmp = convert_int_to_rgb(*(unsigned int *)(obj->tex->addr + obj->tex->line_length * y + x * obj->tex->bits_per_pixel / 8));
	tmp = vec_div_double(tmp, 255);
	return (tmp);
}

t_vector bump_normal(t_object *obj, t_hit_record *rec)
{
	int x;
	int y;
	t_vector tmp;
	t_vector ul, vl, zl;

	// Local = t * UL + b * VL + n * ZL
	x = (int)(rec->u * (double)(obj->bump->width - 1));
	y = (int)(rec->v * (double)(obj->bump->height - 1));
	// x = 1;
	// y = 1;
	// debugPrintDouble("x", "y", x, y);
	// printf("num : %d\n", *(unsigned int *)(obj->bump->addr + obj->bump->line_length * y + x * obj->bump->bits_per_pixel / 8));
	tmp = convert_color_to_normal(*(unsigned int *)(obj->bump->addr + obj->bump->line_length * y + x * obj->bump->bits_per_pixel / 8));
	// debugPrintVec("tmp", &tmp);
	ul = vec_multi_double(rec->e1, tmp.x);
	vl = vec_multi_double(rec->e2, tmp.y);
	zl = vec_multi_double(rec->normal, tmp.z);
	tmp = vec_add(vec_add(ul, vl), zl);
	tmp = vec_unit(tmp);
	return (tmp);
}

t_point ray_at(t_ray ray, double t)
{
	t_point at;

	at = vec_add(ray.orig, vec_multi_double(ray.dir, t));
	return (at);
}

int in_shadow(t_object *objs, t_ray light_ray, double light_len)
{
	t_hit_record rec;

<<<<<<< HEAD
	rec.tmin = 0;
	rec.tmax = light_len;
	if (hit(objs, light_ray, &rec))
		return (TRUE);
	return (FALSE);
=======
    rec.tmin = 0;
    rec.tmax = light_len;
    if (is_ray_hit(objs, light_ray, &rec))
        return (TRUE);
    return (FALSE);
>>>>>>> 06bef7fc0e97a502a9c95895049ceca6fdf38000
}

t_vector reflect(t_vector v, t_vector n)
{
	return (vec_sub(v, vec_multi_double(n, vec_dot(v, n) * 2)));
}

t_vector point_light_get(t_info *info, t_light *light)
{
	t_color diffuse;
	t_vector light_dir;
	double kd; // diffuse의 강도

	t_color specular;
	t_vector view_dir;
	t_vector reflect_dir;

	double light_len;
	t_ray light_ray;

	double spec;
	double ksn;
	double ks;
	double brightness;

	light_dir = vec_sub(light->origin, info->rec.p);
	light_len = vec_len(light_dir);
	// light_ray = ray_init(vec_add(info->rec.p, vec_multi_double(light_dir, EPSILON)), light_dir);
	light_ray = ray_init(vec_add(info->rec.p, vec_multi_double(info->rec.normal, EPSILON)), light_dir);
	// if (in_shadow(info->obj, light_ray, light_len))
	// return (vec_init(0,0,0));
	light_dir = vec_unit(light_dir);
	// 추가끝
	// cosΘ는 Θ 값이 90도 일 때 0이고 Θ가 둔각이 되면 음수가 되므로 0.0보다 작은 경우는 0.0으로 대체한다.
	kd = fmax(vec_dot(info->rec.normal, light_dir), 0.0); // (교점에서 출발하여 광원을 향하는 벡터)와 (교점에서의 법선벡터)의 내적값.
	diffuse = vec_multi_double(light->light_color, kd);
	view_dir = vec_unit(vec_multi_double(info->ray.dir, -1));
	reflect_dir = reflect(vec_multi_double(light_dir, -1), info->rec.normal);
	ksn = 64; // shininess value
	ks = 0.1; // specular strength 강도 계수
	spec = pow(fmax(vec_dot(view_dir, reflect_dir), 0.0), ksn);
	specular = vec_multi_double(vec_multi_double(light->light_color, ks), spec);
	brightness = light->brightness * LUMEN; // 기준 광속/광량을 정의한 매크로
	return (vec_multi_double(vec_add(diffuse, specular), brightness));
}

t_color checkerboard_value(t_hit_record rec)
{
	const int width = 10;
	const int height = 10;
	const double u2 = floor(rec.u * width);
	const double v2 = floor(rec.v * height);
	if (fmod(u2 + v2, 2.) == 0)
		return (rec.albedo);
	return (vec_init(1, 1, 1));
}

t_vector phong_lighting(t_info *info)
{
	t_color light_color;
	t_light *lights;
	t_color color;

	light_color = vec_init(0, 0, 0); //광원이 하나도 없다면, 빛의 양은 (0, 0, 0)일 것이다.
	lights = info->light;
	while (lights) //여러 광원에서 나오는 모든 빛에 대해 각각 diffuse, specular 값을 모두 구해줘야 한다
	{
		light_color = vec_add(light_color, point_light_get(info, lights));
		lights = lights->next;
	}
	light_color = vec_add(light_color, info->ambient);
	if (info->rec.checker)
		color = checkerboard_value((info->rec));
	else
		color = info->rec.albedo;
	return (vec_multi_double(vec_min(vec_multi(light_color, color), vec_init(1, 1, 1)), 255));
}
