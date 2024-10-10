#include "light.h"

t_object	*new_light(t_point3 pos, t_color rgb)
{
	t_object	*object;

	object = galloc(sizeof(t_object));
	if (!object)
		return (0);
	object->data = galloc(sizeof(t_light));
	if (!object->data)
	{
		gfree(object);
		return (0);
	}
	((t_light *)object->data)->pos = pos;
	((t_light *)object->data)->rgb = rgb;
	object->type = o_light;
	return (object);
}

static t_color	get_ambient(t_amb *amb)
{
	if (!amb->is_calc)
	{
		amb->c_rgb = color_scalar(amb->rgb, amb->light);
		amb->is_calc = true;
	}
	return (amb->c_rgb);
}

static t_color	get_light(t_light light)
{
	if (!light.is_calc)
	{
		light.c_rgb = color_scalar(light.rgb, light.bright);
		light.is_calc = true;
	}
	return (light.c_rgb);
}

t_lightning	new_lightning(t_light l, t_point3 p, t_vector3 ev, t_vector3 nv)
{
	return ((t_lightning){.l = l, .p = p, .ev = ev, .nv = nv});
}

// maybe need to blend the colors and fix norminette

t_color	lightning(t_object *obj, t_amb *amb, t_lightning ln)
{
	t_color		eff_color;
	t_color		diff;
	t_color		spec;
	t_vector3	lightv;
	float		l_dot_n;
	t_color		ambient;
	t_vector3	reflectv;
	float		r_dot_e;

	eff_color = color_scalar(obj->mat.color, ln.l.bright);
	lightv = vnormalized(vsub(ln.l.pos, ln.p));
	ambient = get_ambient(amb);
	l_dot_n = vdot(lightv, ln.nv);
	if (l_dot_n < 0)
	{
		diff = color(0, 0, 0);
		spec = color(0, 0, 0);
	}
	else
	{
		diff = color_scalar(eff_color, obj->mat.diff * l_dot_n);
		reflectv = vreflect(vneg(lightv), ln.nv);
		r_dot_e = vdot(reflectv, ln.ev);
	}
	if (r_dot_e < 0 || ft_equalsf(r_dot_e, 0))
		spec = color(0, 0, 0);
	else
	{
		spec = color_scalar(get_light(ln.l), obj->mat.spec
				* powf(r_dot_e, obj->mat.shin));
	}
	return (color_add(ambient, color_add(diff, spec)));
}
