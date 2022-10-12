#include "minirt.h"

t_light	*light_init(t_vector l_origin, t_vector l_color, double br)
{
    t_light *light;

    light = my_calloc(1, sizeof(t_light));
    light->origin = l_origin;
    light->light_color = l_color;
    light->brightness = br;
    return (light);
}

t_sphere	*sphere_init(t_point center, double radius)
{
	t_sphere *init;

 	init = my_calloc(1, sizeof(t_cone));
	init->center = center;
	init->radius = radius;
	return (init);
}

t_plane	*plane_init(t_point center, t_vector normal, double radius)
{
	t_plane *init;

 	init = my_calloc(1, sizeof(t_cone));
	init->center = center;
	init->normal = normal;
    init->radius = radius;
	return (init);
}

t_cylinder	*cylinder_init(t_point center, t_vector normal, \
							double radius, double height);
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
						double radius, double height);
{
	t_cone *init;

	init = my_calloc(1, sizeof(t_cone));
	init->center = center;
	init->radius = radius;
	init->height = height;
    init->normal = normal;
	return (init);
}

t_object	*object_init(t_object_type type, t_vector albedo, 
						void *element, int checker)
{
    t_object    *new;

	new = my_calloc(1, sizeof(t_object));
    new->type = type;
    new->element = element;
    new->albedo = albedo;
    new->checker = checker;
    return (new);
}
