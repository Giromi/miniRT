#include "minirt.h"

static t_vector	_get_cy_side_normal(t_model *cy, t_vector *coor, double h_prime)
{
	t_vector	res;

	coor[C_Q] = vec_mul_const(cy->normal, h_prime);
	res = vec_sub(coor[C_P], coor[C_Q]);
	return (vec_unit(res));
}

void	get_cylinder_uv(t_moment *spot, t_point center, t_vector normal, double size, double r)
{
	double			theta;
	t_vector		e1;
	t_vector		e2;
	double			p_e1;
	double			p_e2;

	(void)r;
	if ((spot->p.x == 0 && spot->p.y == 0 && spot->p.z == 1))
		e1 = vec_unit(vec_cross(vec_init(0, 1, 0), normal));
	else if ((spot->p.x == 0 && spot->p.y == 0 && spot->p.z == -1))
		e1 = vec_unit(vec_cross(vec_init(0, -1, 0), normal));
	else
		e1 = vec_unit(vec_cross(vec_init(0, 0, 1), normal));
	e2 = vec_unit(vec_cross(normal, e1));
	p_e1 = vec_dot(vec_sub(spot->p, center), e1);
	p_e2 = vec_dot(vec_sub(spot->p, center), e2);
	theta = atan2(p_e2, p_e1);
	spot->e1 = e1;
	spot->e2 = e2;
	spot->u = (theta / (M_PI));
	// spot->v = fmod(vec_dot(vec_sub(spot->p, center), normal) / (r * M_PI), 1);
	spot->v = fmod(vec_dot(vec_sub(spot->p, center), normal) / (r * M_PI), 1);
	if (spot->u < 0)
		spot->u += 1;
	// debugPrintVec("spot", &spot->p);
	// debugPrintDouble("u", "v", spot->u, spot->v);
	spot->v = 1 - spot->v;
	spot->u = fmod(spot->u, size) / size;
	spot->v = fmod(spot->v, size) / size;
}

int	ray_at_cylinder(t_object *obj, t_ray ray, t_moment *spot)
{
	const t_cylinder	*cy = obj->elem;
	t_vector			coor[2];
	t_function			func;

	if (get_2d_root(&func, &ray, cy, get_cy_abc) == ERROR)
		return (FALSE);
	func.i = -1;
	while (++func.i < 2)
	{
		spot->t = func.root[func.i];
		if (!is_t_in_range(spot))
			continue ;
		spot->p = ray_at(ray, spot->t);
		coor[C_P] = vec_sub(spot->p, cy->center);
		func.h_prime = (vec_dot(coor[C_P], cy->normal));
		if (is_h_in_range(cy->height, func.h_prime))
			break ;
		if (func.i == 1)
			return (FALSE);
	}
	spot->normal = _get_cy_side_normal(cy, coor, func.h_prime);
	get_cylinder_uv(spot, cy->center, cy->normal, 1, cy->radius);
	get_bump_rgb(&ray, spot, obj);
	flip_normal_face(ray, spot);
	return (TRUE);
}
