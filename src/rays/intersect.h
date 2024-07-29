#ifndef INTERSECT_H
# define INTERSECT_H

# include "rays.h"

typedef struct s_object	t_object;

typedef struct intersect
{
	t_ray			ray;
	t_point3		pos;
	float			t;
	t_object		*object;
	bool			intersected;
}	t_intersect;

#endif