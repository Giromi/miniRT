#include "minirt.h"

void	get_cap_uv(t_moment *spot, t_point center, t_vector normal, double size, double r)
{
	double			theta;
	t_vector		n = spot->normal;
	t_vector		e1;
	t_vector		e2;
	double			p_e1;
	double			p_e2;

	if ((n.x == 0 && n.y == 0 && n.z == 1))
		e1 = vec_unit(vec_cross(vec_init(0, 1, 0), normal));
	else if ((n.x == 0 && n.y == 0 && n.z == -1))
		e1 = vec_unit(vec_cross(vec_init(0, -1, 0), normal));
	else
		e1 = vec_unit(vec_cross(vec_init(0, 0, 1), normal));
	e2 = vec_unit(vec_cross(normal, e1));
	spot->e1 = e1;
	spot->e2 = e2;
	p_e1 = vec_dot(vec_sub(spot->p, center), e1);
	p_e2 = vec_dot(vec_sub(spot->p, center), e2);
	// debugPrintVec("e1", &e1);
	// debugPrintVec("e2", &e);
	// debugPrintDouble("p1", "p2", p_e1, p_e2);
	theta = atan2(p_e2, p_e1);
	spot->u = (theta / (M_PI));
	if (spot->u < 0)
		spot->u += 1;
	spot->v =  vec_len(vec_sub(spot->p, center)) / r;
	// debugPrintVec("spot", &spot->p);
	spot->u = fmod(spot->u, size) / size;
	spot->v = fmod(spot->v, size) / size;
	// debugPrintDouble("u", "v", spot->u, spot->v);
}

int	ray_at_cap(t_object *obj, t_ray ray, t_moment *spot)
{
	t_plane	*pl;
	double	root;
	double	numerator;
	double	denominator;

	pl = (t_plane *)obj->element;
	denominator = vec_dot(ray.dir, pl->normal);
	if (fabs(denominator) < EPSILON)
		return (FALSE);
	numerator = vec_dot(vec_sub(pl->center, ray.orig), pl->normal);
	root = numerator / denominator;
	if (root < spot->tmin || spot->tmax < root)
		return (FALSE);
	spot->t = root;
	spot->p = ray_at(ray, root);
	// debugPrintVec("pl center", &pl->center);
    t_vector pcv = vec_sub(spot->p, pl->center);
    if (vec_dot(pcv, pcv) > pl->radius * pl->radius)
        return (FALSE);
	spot->albedo = obj->albedo;
	spot->normal = pl->normal;
	get_cap_uv(spot, pl->center, pl->normal, 1, pl->radius);
	if (obj->bump)
	{
		// if (obj->tex->img_ptr)
		//     spot->albedo = tex_rgb(obj, spot);
		spot->normal = bump_normal(obj, spot);
	}
	flip_normal_face(ray, spot);
	return (TRUE);
}

void	get_plane_uv(t_moment *spot, t_point center, double size)
{
	const t_vector		p = vec_sub(spot->p, center);
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
	spot->u = fmod(vec_dot(e1, p), size) / size;
	spot->v = fmod(vec_dot(e2, p), size) / size;
	spot->u += spot->u < 0;
	spot->v += spot->v < 0;
	spot->v = 1 - spot->v;
}

int	ray_at_plane(t_object *obj, t_ray ray, t_moment *spot)
{
	const t_plane	*pl = obj->elem;
	double	val[3];

	val[NUMERATOR] = vec_dot(ray.dir, pl->normal);
	if (fabs(val[NUMERATOR]) < EPSILON)
		return (FALSE);
	 = vec_dot(vec_sub(pl->center, ray.orig), pl->normal);
	root = numerator / denominator;
	if (root < spot->tmin || spot->tmax < root)
		return (FALSE);
	spot->t = root;
	spot->p = ray_at(ray, root);
	spot->albedo = obj->albedo;
	spot->normal = pl->normal;
	get_plane_uv(spot, pl->center, 10); //조정 바람
	get_bump_rgb(&ray, spot, obj);
	flip_normal_face(ray, spot);
	return (TRUE);
}
