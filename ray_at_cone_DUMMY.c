#include "minirt.h"



// int	ray_at_conlinder(t_object *obj, t_ray ray, t_moment *spot)
// {
// 	t_conlinder	*cn;
// 	double		a;
// 	double		half_b;
// 	double		c;
// 	double		dis;
// 	double		sqrtd;
// 	double		root;
// 	double	m;
// 	t_vector	w;

// 	cn = (t_conlinder *)obj->element;
// 	w = vec_sub(ray.orig, cn->center);
// 	m = cn->radius2 / (cn->height * cn->height);
// 	double	v_n_pow = (vec_dot(ray.dir, cn->normal)) * (vec_dot(ray.dir, cn->normal));
// 	double	v_n_dot_w_n = (vec_dot(ray.dir, cn->normal) * vec_dot(w, cn->normal));
// 	double	w_n_pow = vec_dot(w, cn->normal) * (vec_dot(w, cn->normal));
// 	a = vec_dot(ray.dir, ray.dir) - ((m + 1) * v_n_pow);
// 	half_b = vec_dot(ray.dir, w) - ((m + 1) * v_n_dot_w_n) + (m * cn->height * vec_dot(ray.dir, cn->normal));
// 	c = vec_dot(w, w) - ((m + 1) * w_n_pow) + (2 * m * cn->height * vec_dot(w, cn->normal)) - cn->radius2;
// 	dis = half_b * half_b - a * c;
// 	if (dis < 0)
// 		return (FALSE);
// 	sqrtd = sqrt(dis);
// 	root = (-half_b - sqrtd) / a;
// 	spot->t = root;
// 	spot->p = ray_at(ray, root);
// 	if (vec_dot(vec_sub(spot->p, cn->center), cn->normal) < 0
//         || vec_dot(vec_sub(spot->p, cn->center), cn->normal) > cn->height
// 		|| (root < spot->tmin || spot->tmax < root))
// 	{
// 		root = (-half_b + sqrtd) / a;
// 		if (root < spot->tmin || spot->tmax < root)
// 			return (FALSE);
// 		spot->t = root;
// 		spot->p = ray_at(ray, root);
// 	}
//     if (root < spot->tmin || spot->tmax < root)
// 		return (FALSE);
// 	double	nom = vec_len_pow(vec_sub(vec_sub(spot->p, cn->center), vec_mul_const(cn->normal, cn->height)));
// 	double	denom = cn->height - vec_dot(vec_sub(spot->p, cn->center), cn->normal);
// 	double	a_c = cn->height - (nom / denom);
// 	spot->normal = vec_unit(vec_sub(spot->p, vec_add(cn->center, vec_mul_const(cn->normal, a_c))));
// 	spot->albedo = obj->albedo;
// 	flip_normal_face(ray, spot);
// 	if (0 <= vec_dot(vec_sub(spot->p, cn->center), cn->normal) &&
//     	vec_dot(vec_sub(spot->p, cn->center), cn->normal) <= cn->height && (root >= spot->tmin || spot->tmax >= root))
// 	{
// 		get_cylinder_uv(spot, cn->center, cn->normal, 1, cn->radius);
// 		if (obj->bump->file_name)
// 		{
// 			// printf("asdasd\n");
// 			// spot->albedo = tex_rgb(obj, spot);
// 			if (obj->tex->img_ptr)
// 				spot->albedo = tex_rgb(obj, spot);
// 			spot->normal = bump_normal(obj, spot);
// 			flip_normal_face(ray, spot);
// 		}
// 		return (TRUE);
// 	}
//     return (FALSE);
// }



	// if ((0 <= func.h_prime && func.h_prime <= cn->height) && \
	// 		(spot->tmin <= spot->t && spot->t <= spot->tmax));	일단 있었음
		// return (FALSE);
