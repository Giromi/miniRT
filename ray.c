#include "minirt.h"

void	get_bump_rgb(t_ray *ray, t_moment *spot, t_object *obj)
{
	if (!(obj->type & BM))
		return ;
	if (obj->tex->img_ptr)
		spot->albedo = tex_rgb(obj, spot);
	spot->normal = bump_normal(obj, spot);
}

t_vector convert_int_to_rgb(int color)
{
	t_vector res;

	res.x = color >> 16 & 0xFF;
	res.y = color >> 8 & 0xFF;
	res.z = color & 0xFF;
	return (res);
}

t_vector tex_rgb(t_object *obj, t_moment *spot)
{
	int x;
	int y;
	t_vector tmp;

	x = (int)(spot->u * obj->tex->width);
	y = (int)(spot->v * obj->tex->height);
	tmp = convert_int_to_rgb(*(unsigned int *)(obj->tex->addr + obj->tex->line_length * y + x * obj->tex->bits_per_pixel / 8));
	tmp = vec_div_const(tmp, 255);
	return (tmp);
}

t_vector bump_normal(t_object *obj, t_moment *spot)
{
	int x;
	int y;
	t_vector tmp;
	t_vector ul, vl, zl;

	// Local = t * UL + b * VL + n * ZL
	x = (int)(spot->u * (double)(obj->bump->width - 1));
	y = (int)(spot->v * (double)(obj->bump->height - 1));
	// x = 1;
	// y = 1;
	// debugPrintDouble("x", "y", x, y);
	// printf("num : %d\n", *(unsigned int *)(obj->bump->addr + obj->bump->line_length * y + x * obj->bump->bits_per_pixel / 8));
	tmp = convert_color_to_normal(*(unsigned int *)(obj->bump->addr + obj->bump->line_length * y + x * obj->bump->bits_per_pixel / 8));
	// debugPrintVec("tmp", &tmp);
	ul = vec_mul_const(spot->e1, tmp.x);
	vl = vec_mul_const(spot->e2, tmp.y);
	zl = vec_mul_const(spot->normal, tmp.z);
	tmp = vec_add(vec_add(ul, vl), zl);
	tmp = vec_unit(tmp);
	return (tmp);
}

t_point ray_at(t_ray ray, double t)
{
	t_point at;

	at = vec_add(ray.orig, vec_mul_const(ray.dir, t));
	return (at);
}

int in_shadow(t_object *objs, t_ray light_ray, double light_len)
{
	t_moment spot;

    spot.tmin = 0;
    spot.tmax = light_len;
    if (hit(objs, light_ray, &spot))
        return (TRUE);
    return (FALSE);
}

t_vector reflect(t_vector v, t_vector n)
{
	return (vec_sub(v, vec_mul_const(n, vec_dot(v, n) * 2)));
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

	light_dir = vec_sub(light->origin, info->spot.p);
	light_len = vec_len(light_dir);
	// light_ray = ray_init(vec_add(info->spot.p, vec_mul_const(light_dir, EPSILON)), light_dir);
	light_ray = ray_init(vec_add(info->spot.p, vec_mul_const(info->spot.normal, EPSILON)), light_dir);
	// if (in_shadow(info->obj, light_ray, light_len))
	// return (vec_init(0,0,0));
	light_dir = vec_unit(light_dir);
	// 추가끝
	// cosΘ는 Θ 값이 90도 일 때 0이고 Θ가 둔각이 되면 음수가 되므로 0.0보다 작은 경우는 0.0으로 대체한다.
	kd = fmax(vec_dot(info->spot.normal, light_dir), 0.0); // (교점에서 출발하여 광원을 향하는 벡터)와 (교점에서의 법선벡터)의 내적값.
	diffuse = vec_mul_const(light->light_color, kd);
	view_dir = vec_unit(vec_mul_const(info->ray.dir, -1));
	reflect_dir = reflect(vec_mul_const(light_dir, -1), info->spot.normal);
	ksn = 64; // shininess value
	ks = 0.1; // specular strength 강도 계수
	spec = pow(fmax(vec_dot(view_dir, reflect_dir), 0.0), ksn);
	specular = vec_mul_const(vec_mul_const(light->light_color, ks), spec);
	brightness = light->brightness * LUMEN; // 기준 광속/광량을 정의한 매크로
	return (vec_mul_const(vec_add(diffuse, specular), brightness));
}

t_color checkerboard_value(t_moment spot)
{
	const int width = 10;
	const int height = 10;
	const double u2 = floor(spot.u * width);
	const double v2 = floor(spot.v * height);
	if (fmod(u2 + v2, 2.) == 0)
		return (spot.albedo);
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
	if (info->spot.checker)
		color = checkerboard_value((info->spot));
	else
		color = info->spot.albedo;
	return (vec_mul_const(vec_min(vec_mul(light_color, color), vec_init(1, 1, 1)), 255));
}
