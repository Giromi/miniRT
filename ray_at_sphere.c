#include "minirt.h"

void get_sphere_uv(t_moment *spot, t_point center, double size)
{
	double phi;
	double theta;
	const t_vector n = spot->normal;
	t_vector e1;
	t_vector e2;

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

int ray_at_sphere(t_object *obj, t_ray ray, t_moment *spot)
{
	const t_sphere	*sp = obj->elem;
	t_function		func;
	t_vector		cp;

	if (get_2d_root(&func, &ray, sp, get_sp_abc) == ERROR)
		return (FALSE);
	func.i = -1;
	spot->t = func.root[0];
	spot->t = func.root[!is_t_in_range(spot)];
	if (spot->t < spot->tmin || spot->tmax < spot->t)
		return (FALSE);
	spot->p = ray_at(ray, spot->t);
	cp = vec_sub(spot->p, sp->center);
	spot->normal = vec_div_const(cp, sp->radius);
	get_sphere_uv(spot, sp->center, 1);
	get_bump_rgb(&ray, spot, obj);
	flip_normal_face(ray, spot);
	return (TRUE);
}
