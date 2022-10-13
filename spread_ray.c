#include "minirt.h"

static int _ray_at_obj(t_object *obj, t_ray ray, t_hit_record *rec)
{
	int  hit_result;

	hit_result = FALSE;
	if (obj->type & PL)
		hit_result = ray_at_plane(obj, ray, rec);
	else if (obj->type & SP)
        hit_result = ray_at_sphere(obj, ray, rec);
    else if (obj->type & CY)
        hit_result = ray_at_cylinder(obj, ray, rec);
	else if (obj->type & CN)
        hit_result = ray_at_cone(obj, ray, rec);
	else if (obj->type & CP)
        hit_result = ray_at_cap(obj, ray, rec);
    return (hit_result);
}

int is_ray_hit(t_object *obj, t_ray ray, t_hit_record *rec)
{
	int	hit_flag;

	hit_flag = FALSE;
	while(obj)
	{
		hit_flag = _ray_at_obj(obj, ray, rec);
		if (hit_flag)
			rec->tmax = rec->t;
		obj = obj->next;
	}
	return (hit_flag);
}
