#include "minirt.h"

void	get_sphere_uv(t_moment *spot, t_point center, double size)
{
	double			phi;
	double			theta;
	const t_vector		n = spot->normal;
	t_vector			e1;
	t_vector			e2;

	if ((n.x == 0 && n.y == 1 && n.z == 0))
		e1 = vec_unit(vec_cross(vec_init(0, 0, -1), n));
	else if ((n.x == 0 && n.y == -1 && n.z == 0))
		e1 = vec_unit(vec_cross(vec_init(0, 0, 1), n));
	else
		e1 = vec_unit(vec_cross(vec_init(0, 1, 0), n));
	e2 = vec_unit(vec_cross(n, e1));
	spot->e1 = e1;
	spot->e2 = e2;
	theta = atan2((spot->p.x - center.x), (spot->p.z - center.z));
	phi = acos((spot->p.y - center.y) / vec_len(vec_sub(spot->p, center)));
	spot->u = (theta / (M_PI));
	spot->v = phi / M_PI;
	if (spot->u < 0)
		spot->u += 1;
	spot->u = fmod(spot->u, size) / size;
	spot->v = fmod(spot->v, size) / size;
}

int	ray_at_sphere(t_object *obj, t_ray ray, t_moment *spot)
{
	t_sphere	*sp;
	t_vector		oc;
	double		a;
	double		c;
	double		dis;
	double		half_b;
	double		sqrtd;
	double		root;

	sp = (t_sphere *)obj->element;
	oc = vec_sub(ray.orig, ((t_sphere*)obj->element)->center);
	a = vec_len_sqr(ray.dir);
	half_b = vec_dot(oc, ray.dir);
	c = vec_len_sqr(oc) - ((t_sphere*)obj->element)->radius2;
	dis = half_b * half_b - a * c;
	if (dis < 0)
		return (FALSE);
	sqrtd = sqrt(dis);
	root = (-half_b - sqrtd) / a;
	if (root < spot->tmin || spot->tmax < root)
		root = (-half_b + sqrtd) / a;
    if (root < spot->tmin || spot->tmax < root)
		return (FALSE);
	spot->albedo = obj->albedo;
	spot->t = root;
	spot->p = ray_at(ray, root);
	spot->normal = vec_div_const(vec_sub(spot->p, ((t_sphere*)obj->element)->center), ((t_sphere*)obj->element)->radius);
	get_sphere_uv(spot, sp->center, 1); //조정 바람
	if (obj->bump->file_name)
	{
		// spot->albedo = tex_rgb(obj, spot);
		if (obj->tex->img_ptr)
			spot->albedo = tex_rgb(obj, spot);
		spot->normal = bump_normal(obj, spot);
	}
	flip_normal_face(ray, spot);
	return (TRUE);
}
