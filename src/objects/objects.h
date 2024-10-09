#ifndef OBJECTS_H
# define OBJECTS_H

# include "betterft.h"
# include "../vectors/vectors.h"
# include "../rays/intersect.h"
# include "../color/color.h"

//	t_objects_type: The type of object
typedef enum e_objects_type
{
	o_plane,
	o_sphere,
	o_light,
	o_cylin,
}	t_objects_type;

// t_scene: A linked list of objects
typedef t_list			t_scene;

typedef struct s_material
{
	t_color	color;
	float	ambient;
	float	diffuse;
	float	specular;
	float	shininess;
}	t_material;

//	t_object: An object in the scene
typedef struct s_object	t_object;

typedef struct s_object
{
	t_objects_type	type;
	void			*data;
	t_xs			(*intersect)(t_object *, t_ray);
	bool			(*does_intersect)(t_ray, t_object *);
	t_vector3		(*normal_at)(t_object *, t_point3);
	t_matrix4		transform;
	t_material		material;
}	t_object;

//	material: Create a new material
//	Default color is green
//	@param ambient The ambient value
//	@param diffuse The diffuse value
//	@param specular The specular value
//	@param shininess The shininess value
//	@return A new material
t_material	material(float ambient, float diffuse,
	float specular, float shininess);

//	dfmaterial: Create a new default material
//	Default color is green
//	@return A new default material
t_material	dfmaterial(void);

//	does_intersect: Check if a ray intersects any object in the object list
//	@param ray The ray to check
//	@param scene The object list to check
//	@return true if the ray intersects any object, false otherwise
bool		does_intersect(t_ray ray, t_scene *scene);

//	intersect: Check if a ray intersects any object in the object list
//	Also updates the intersection data
//	@param intersect The intersection data
//	@param scene The object list to check
//	@return true if the ray intersects any object, false otherwise
bool		intersect(t_intersect *intersect, t_scene *scene);

//	set_transform: Set the transformation matrix of an object
//	@param obj The object to transform
//	@param transform The transformation matrix
void		set_transform(t_object *obj, t_matrix4 transform);

#endif
