/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 22:50:41 by rude-jes          #+#    #+#             */
/*   Updated: 2024/10/28 22:50:41 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "compute.h"
#include "../miniRT.h"
#include "ft_memory.h"
#include "lightning.h"

//	compute_refractive_indices: Compute the refractive indices
//	@param cs The precomputed intersection
//	@param hit The hit intersection
//	@param xs_parent The parent intersection set
static inline void	compute_refractive_indices(t_comps *cs,
	t_intersect *hit, t_xs_parent xs_parent)
{
	int			idx;
	t_list		*objs;

	objs = 0;
	idx = -1;
	while (idx++, idx < xs_parent.count)
	{
		if (xs_parent.xs + idx == hit)
		{
			cs->n1 = 1.0;
			if (objs)
				cs->n1 = ((t_object *)(objs->content))->mat.refract_idx;
		}
		if (ft_lstremove(&objs, xs_parent.xs[idx].object, 0))
			ft_lstnew_front(&objs, xs_parent.xs[idx].object);
		if (xs_parent.xs + idx == hit)
		{
			cs->n2 = 1.0;
			if (objs)
				cs->n2 = ((t_object *)(objs->content))->mat.refract_idx;
			break ;
		}
	}
	ft_lstclear(&objs, 0);
}

//	precompute: Precompute the intersection
//	@param i The intersection
//	@param r The ray
//	@param xs_parent The parent intersection set
//	@param fast If the computation should be fast
//	@return The precomputed intersection
static inline t_comps	precompute(t_intersect *i, t_ray r,
	t_xs_parent xs_parent, bool fast)
{
	t_comps	comps;

	(void)fast;
	ft_bzero(&comps, sizeof(t_comps));
	comps.t = i->t;
	comps.object = i->object;
	comps.point = ray_at(r, comps.t);
	comps.eyev = vneg(r.direction);
	comps.normalv = normal_at(comps.object, comps.point);
	if (vdot(comps.normalv, comps.eyev) < 0 && !ft_equalsd(comps.t, 0))
	{
		comps.inside = true;
		comps.normalv = vneg(comps.normalv);
	}
	else
		comps.inside = false;
	comps.over_point = vadd(comps.point, vmul(comps.normalv, EPSILOND));
	comps.under_point = vsub(comps.point, vmul(comps.normalv, EPSILOND));
	comps.reflectv = vreflect(r.direction, comps.normalv);
	compute_refractive_indices(&comps, i, xs_parent);
	return (comps);
}

//	compute_phong: Compute the Phong lightning
//	@param comps The precomputed intersection
//	@param ln The lightning
//	@param fast If the computation should be fast
//	@return The Phong lightning
static inline t_color	compute_phong(t_comps *comps,
	t_lightning *ln, bool fast)
{
	t_minirt	*minirt;
	t_color		c;
	t_lights	*lights;

	minirt = get_minirt();
	c = color(0, 0, 0);
	*ln = new_lightning(0, comps->point,
			comps->eyev, comps->normalv);
	ln->amb = minirt->world.amb;
	lights = minirt->world.lights;
	while (lights)
	{
		ln->l = lights->content;
		c = color_add(c, lightning(comps->object, *ln,
					(is_shadowed(minirt->world.scene,
							comps->point, ln->l)), fast));
		lights = lights->next;
	}
	return (c);
}

//	shade_hit: Shade the hit
//	@param comps The precomputed intersection
//	@param fast If the computation should be fast
//	@param remaining The remaining reflections
//	@return The color of the hit
static inline t_color	shade_hit(t_comps *comps, bool fast, int remaining)
{
	t_lightning	ln;
	t_mat		*material;
	t_color		c[3];
	double		reflectance;

	c[0] = compute_phong(comps, &ln, fast);
	c[1] = reflected_color(comps, fast, remaining);
	c[2] = refracted_color(comps, fast, remaining);
	material = &comps->object->mat;
	if (material->reflect > 0 && material->transp > 0)
	{
		reflectance = schlick(comps);
		return (color_add(c[0], color_add(color_scalar(c[1], reflectance),
					color_scalar(c[2], 1 - reflectance))));
	}
	return (color_add(color_add(c[0], c[1]), c[2]));
}

t_color	color_at(t_ray r, bool fast, int remaining)
{
	t_xs_parent	xs_parent;
	t_intersect	*i;
	t_comps		comps;
	t_minirt	*minirt;

	if (fast && remaining >= MAX_REFLECT)
		remaining = 1;
	minirt = get_minirt();
	xs_parent = intersect_world(minirt->world.scene, r);
	i = hit(xs_parent);
	if (!i)
	{
		gfree(xs_parent.xs);
		return (color_scalar(minirt->world.amb->rgb, minirt->world.amb->light));
	}
	comps = precompute(i, r, xs_parent, fast);
	gfree(xs_parent.xs);
	return (shade_hit(&comps, fast, remaining));
}
