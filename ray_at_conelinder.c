#include "minirt.h"

static t_vector	_get_cy_side_normal(t_model *cy, t_vector *coor, double h_prime)
{
	t_vector	res;

	coor[C_Q] = vec_mul_const(cy->normal, h_prime);
	res = vec_sub(coor[C_P], coor[C_Q]);
	return (vec_unit(res));
}

static t_vector	_get_cn_side_normal(t_moment *spot, t_cone *cn, t_vector *coor)
{
	t_vector	res;
	t_vector	ac_vec;
	double		val[3];

	coor[C_H] = vec_mul_const(cn->normal, cn->height);
	val[NUMERATOR] = vec_len_sqr(vec_sub(coor[C_P], coor[C_H]));
	if (fabs(val[NUMERATOR]) < EPSILON)
		return (vec_init(0, 0, 0));
	val[DENOMINATOR] = cn->height - vec_dot(coor[C_P], cn->normal);
	val[TARGET] = cn->height - (val[NUMERATOR] / val[DENOMINATOR]);
	ac_vec = vec_mul_const(cn->normal, val[TARGET]);
	res = vec_sub(coor[C_P], ac_vec);
	return (vec_unit(res));
}

void	get_conelinder_uv(t_moment *spot, t_model *cny, double size)
{
	t_vector		n = spot->normal;
	t_vector		basis_vec;
	double			theta;
	double			theta;
	double			p_[2];

	if ((n.x == 0 && n.y == 0 && n.z == 1))
		basis_vec = vec_init(0, 1, 0);
	else if ((n.x == 0 && n.y == 0 && n.z == -1))
		basis_vec = vec_init(0, -1, 0);
	else
		basis_vec = vec_init(0, 0, 1);
	spot->e1 = vec_unit(vec_cross(basis_vec, n));
	spot->e2 = vec_unit(vec_cross(n, spot->e1));
	p_[E_ONE] = vec_dot(vec_sub(spot->p, cny->center), spot->e1);
	p_[E_TWO] = vec_dot(vec_sub(spot->p, cny->center), spot->e2);
	theta = atan2(p_[E_TWO], p_[E_ONE]);
	spot->u = (theta / (M_PI));
	spot->v = fmod(vec_dot(vec_sub(spot->p, cny->center), n) \
				/ (cny->radius * M_PI), 1);
	spot->u += spot->u < 0;
	spot->v = 1 - spot->v;
	spot->u = fmod(spot->u, size) / size;
	spot->v = fmod(spot->v, size) / size;
}

int	ray_at_cone(t_object *obj, t_ray ray, t_moment *spot)
{
	const t_cone	*cn = obj->elem;
	t_vector		coor[2];
	t_function		func;

	if (get_2d_root(&func, &ray, cn, get_cn_abc) == ERROR)
		return (FALSE);
	func.i = -1;
	while (++func.i < 2)
	{
		spot->t = func.root[func.i];
		spot->p = ray_at(ray, spot->t);
		coor[C_P] = vec_sub(spot->p, cn->center);
		func.h_prime = (vec_dot(coor[C_P], cn->normal));
		if (is_ray_in_obj(spot, cn->height, func.h_prime, obj->type))
			break ;
		if (func.i == 1)
			return (FALSE);
	}
	spot->normal = _get_cn_side_normal(spot, cn, coor);
	if (spot->normal.x == 0 && spot->normal.y == 0 && spot->normal.z == 0)
		return (FALSE);
	get_cylinder_uv(spot, cn->center, cn->normal, 1, cn->radius);
	get_bump_rgb(&ray, spot, obj);
	flip_normal_face(ray, spot);
	return (TRUE);
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
