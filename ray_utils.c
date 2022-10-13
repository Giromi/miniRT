#include "minirt.h"

void	get_bump_rgb(t_ray *ray, t_moment *spot, t_object *obj)
{
	if (!(obj->type & BM))
		return ;
	if (obj->tex->img_ptr)
		spot->albedo = tex_rgb(obj, spot);
	spot->normal = bump_normal(obj, spot);
}

int	is_t_in_range(t_moment *spot)
{
	return (spot->tmin <= spot->t && spot->t <= spot->tmax);
}

int	is_h_in_range(double h, double h_prime)
{
	return (0 <= h_prime && h_prime <= h);
}
