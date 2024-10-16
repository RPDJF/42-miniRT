#include "rays.h"

t_point3	ray_at(t_ray ray, double t)
{
	return ((t_point3)vadd((t_vector3)ray.origin, vmul(ray.direction, t)));
}

t_ray	ray(t_point3 origin, t_vector3 direction)
{
	t_ray	ray;

	ray.origin = origin;
	ray.direction = direction;
	return (ray);
}

t_ray	transform(t_ray r, t_matrix4 m)
{
	t_ray	transformed;

	transformed.origin = tm4mul(m, r.origin);
	transformed.direction = tm4mul(m, r.direction);
	return (transformed);
}
