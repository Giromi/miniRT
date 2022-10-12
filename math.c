#include "minirt.h"

void	get_cy_abc(double *term, t_ray *ray, t_model *cy)
{
	t_vector		w;
	const double	r_pow_2 = cy->radius * cy->radius;
	double			dot_val[3];

	w = vec_sub(ray->orig, cy->center);
	dot_val[V_N] = vec_dot(ray->dir, cy->normal);
	dot_val[W_V] = vec_dot(w, ray->dir);
	dot_val[W_N] = vec_dot(w, cy->normal);
	term[A] = vec_len_pow(ray->dir) - dot_val[V_N] * dot_val[V_N];
	term[B] = dot_val[W_V] - ((vec_dot(ray->dir, cy->normal)) *  dot_val[W_N]);
	term[C] = vec_len_sqr(w) - (dot_val[W_N] * dot_val[W_N]) - r_pow_2;
}

void	get_cn_abc()
{

}

int	get_2d_root(double *term, double *root)
{
	double	judge;

	judge = (term[B] * term[B]) - (term[A] * term[C]);
	if (judge < 0)
		return (ERROR);
	root[0] =  (-term[B] - sqrtd(judge)) / term[A];
	root[1] =  (-term[B] + sqrtd(judge)) / term[A];
}
