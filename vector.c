#include "minirt.h"

t_vector  vec_min(t_vector vec1, t_vector vec2)
{
    if (vec1.x > vec2.x)
        vec1.x = vec2.x;
    if (vec1.y > vec2.y)
        vec1.y = vec2.y;
    if (vec1.z > vec2.z)
        vec1.z = vec2.z;
    return (vec1);
}

t_vector	vec_add(t_vector u, t_vector v)
{
    t_vector   init;

    init.x = u.x + v.x;
    init.y = u.y + v.y;
    init.z = u.z + v.z;
    return (init);
}

t_vector	vec_once_add_point(t_point o, t_vector a, t_vector b, \
																	t_vector c)
{
    t_vector   init;

    init.x = o.x + a.x + b.x + c.x;
    init.y = o.y + a.y + b.y + c.y;
    init.z = o.z + a.z + b.z + c.z;
    return (init);
}

t_vector	vec_sub(t_vector u, t_vector v)
{
    t_vector   init;

    init.x = u.x - v.x;
    init.y = u.y - v.y;
    init.z = u.z - v.z;
    return (init);
}

t_vector	vec_multi(t_vector u, t_vector v)
{
    t_vector   init;

    init.x = u.x * v.x;
    init.y = u.y * v.y;
    init.z = u.z * v.z;
    return (init);
}

t_vector	vec_div(t_vector u, t_vector v)
{
    t_vector   init;

    if (v.x == 0 || v.y == 0 || v.z == 0)
        ft_strerror("0 넣지마");
    init.x = u.x / v.x;
    init.y = u.y / v.y;
    init.z = u.z / v.z;
    return (init);
}

t_vector	vec_multi_double(t_vector u, double n)
{
    t_vector   init;

    init.x = u.x * n;
    init.y = u.y * n;
    init.z = u.z * n;
    return (init);
}

t_vector	vec_div_double(t_vector u, double n)
{
    // t_vector   init;

    // init.x = u.x / n;
    // init.y = u.y / n;
    // init.z = u.z / n;
    // return (init);
    return (vec_multi_double(u, (1 / n)));
}

double	vec_dot(t_vector u, t_vector v)
{
	return (u.x * v.x + u.y * v.y + u.z * v.z);
}

t_vector	vec_cross(t_vector u, t_vector v)
{
	t_vector init;
	
	init.x = u.y * v.z - u.z * v.y;
	init.y = u.z * v.x - u.x * v.z;
	init.z = u.x * v.y - u.y * v.x;
	return (init);
}

double	vec_len(t_vector u)
{
	return (sqrt(pow(u.x, 2.0) + pow(u.y, 2.0) + pow(u.z, 2.0)));
}
double	vec_len_sqr(t_vector u)
{
    return (pow(u.x, 2.0) + pow(u.y, 2.0) + pow(u.z, 2.0));
}
t_vector	vec_unit(t_vector u)
{
	return (vec_div_double(u, vec_len(u)));
}
t_vector	vec_init(double x, double y, double z)
{
	t_vector init;
	
	init.x = x;
	init.y = y;
	init.z = z;
	return (init);
}
