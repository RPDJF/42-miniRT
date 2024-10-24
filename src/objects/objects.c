#include "objects.h"

t_mat	material(t_color color, double diff,
	double spec, double shininess)
{
	return ((t_mat){
		.color = color,
		.diff = diff,
		.spec = spec,
		.shin = shininess,
		.reflect = 0.5,
		.transp = 0.5,
		.refract_idx = 1.5,
		.pattern = pattern(),
		.bumpmap = dfbumpmap()
	});
}

t_mat	dfmaterial(t_color color)
{
	return ((t_mat){
		.color = color,
		.diff = 0.6,
		.spec = 0.2,
		.shin = 50,
		.reflect = 0.1,
		.transp = 0.0,
		.refract_idx = 1.0,
		.pattern = pattern(),
		.bumpmap = dfbumpmap()
	});
}

void	set_transform(t_object *obj, t_matrix4 transform)
{
	obj->transform = m4mul(obj->transform, transform);
}
