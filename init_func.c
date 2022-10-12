#include "minirt.h"

t_sphere	*sp_init(t_point center, double radius)
{
	t_sphere *init;

 	init = my_calloc(1, sizeof(t_cone));
	init->center = center;
	init->radius = radius;
	return (init);
}

t_plane	*pl_init(t_point center, t_vector normal, double radius)
{
	t_plane *init;

 	init = my_calloc(1, sizeof(t_cone));
	init->center = center;
	init->normal = normal;
    init->radius = radius;
	return (init);
}

t_cylinder	*cy_init(t_point center, t_vector normal, \
							double radius, double height)
{
	t_cylinder *init;

	init = my_calloc(1, sizeof(t_cone));
	init->center = center;
	init->radius = radius;
	init->height = height;
    init->normal = normal;
	return (init);
}

t_cone		*cone_init(t_point center, t_vector normal, \
						double radius, double height)
{
	t_cone *init;

	init = my_calloc(1, sizeof(t_cone));
	init->center = center;
	init->radius = radius;
	init->height = height;
    init->normal = normal;
	return (init);
}

t_object	*obj_init(t_object_type type, t_vector albedo, 
						t_model *element)
{
    t_object    *new;

	new = my_calloc(1, sizeof(t_object));
    new->type = type;
    new->elem = element;
    new->albedo = albedo;
    return (new);
}
