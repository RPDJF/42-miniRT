#include "sphere.h"

//  intersect_sphere: Check if ray intersects sphere and update
//  intersection data
//  @param intersect The intersection data
//  @param object The object to check
//	math: if t1 > RAY_T_MIN && t1 < intersect->t, intersect->t = t1
//	math: if t2 > RAY_T_MIN && t2 < intersect->t, intersect->t = t2
//  @return true if the ray intersects the sphere, false otherwise
static t_xs_parent	intersect_sphere(t_object *object, t_ray ray)
{
	t_xs_parent		inters;
	double			a;
	double			b;
	double			c;
	t_point3		sphere_to_ray;

	inters = xs();
	ray = transform(ray, object->inv_transform);
	sphere_to_ray = vsub(ray.origin, point3(0, 0, 0));
	a = vdot(ray.direction, ray.direction);
	b = 2 * (vdot(ray.direction, sphere_to_ray));
	c = vdot(sphere_to_ray, sphere_to_ray) - 1;
	if (quadratic_intersection(a, b, c, object))
	{
		add_intersection(&inters, intersection(object->t[0], object));
		add_intersection(&inters, intersection(object->t[1], object));
	}
	return (inters);
}

//  uv_mapping_sphere: Map a point on the sphere to a uv coordinate
//  @param object_p The point on the sphere
//  @return The uv coordinate
static t_vector2	uv_mapping_sphere(t_point3 obj_p)
{
	double		phi;
	double		theta;

	theta = atan2(obj_p.z, obj_p.x);
	phi = acos(obj_p.y);
	return (vector2((theta + M_PI) / (2 * M_PI), phi / M_PI));
}

//  normal_at_sphere: Get the normal at a point on the sphere
//  @param object The object
//  @param world_point The point on the sphere
//  @return The normal at the point
static t_vector3	normal_at_sphere(t_object *object, t_point3 world_point)
{
	t_point3	object_p;
	t_vector3	object_n;
	t_vector3	world_n;

	object_p = tm4mul(object->inv_transform, world_point);
	object_n = vsub(object_p, point3(0, 0, 0));
	if (object->mat.bumpmap)
		object_n = perturbn(object_n,
				get_bumpv(object->mat.bumpmap, uv_mapping_sphere(object_p)));
	world_n = tm4mul(object->tinv_transform, object_n);
	world_n.w = VECTOR;
	vnormalize(&world_n);
	return (world_n);
}

t_object	*new_sphere(t_point3 origin, double radius, t_color color)
{
	t_object	*object;

	origin.w = POINT;
	object = galloc(sizeof(t_object));
	if (!object)
		return (0);
	object->data = galloc(sizeof(t_sphere));
	if (!object->data)
	{
		gfree(object);
		return (0);
	}
	*((t_sphere *)object->data) = (t_sphere){.origin = origin,
		.radius = radius};
	*object = (t_object){.data = object->data, .mat = dfmaterial(color),
		.intersect = intersect_sphere, .type = o_sphere,
		.normal_at = normal_at_sphere};
	object->transform = m4mul(m4translation(origin),
			m4scaling(vector3(radius, radius, radius)));
	object->inv_transform = m4invert(object->transform, 0);
	object->tinv_transform = m4transpose(object->inv_transform);
	return (object);
}
