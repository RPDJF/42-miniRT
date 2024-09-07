#ifndef VECTORS_H
# define VECTORS_H

# include "../../libs/betterft/betterft.h"
# include "math.h"

# ifndef M_PI
#  define M_PI 3.14159265358979323846f
# endif

typedef struct s_vector2
{
	double	u;
	double	v;
}	t_vector2;

typedef struct s_vector3
{
	double	x;
	double	y;
	double	z;
}	t_vector3;

typedef t_vector3	t_point3;

//	vector2: Create a new 2D vector
//	@param u The u component
//	@param v The v component
//	@return A new 2D vector
t_vector2	vector2(double u, double v);

//	vector3: Create a new 3D vector
//	@param x The x component
//	@param y The y component
//	@param z The z component
//	@return A new 3D vector
t_vector3	vector3(double x, double y, double z);

//	point3: Create a new 3D point
//	@param x The x component
//	@param y The y component
//	@param z The z component
//	@return A new 3D point
t_point3	point3(double x, double y, double z);

//	vlength: Get the length of a vector
//	@param v The vector
//	@return The length of the vector
double		vlength(t_vector3 v);

//	vlength2: Get the squared length of a vector
//	@param v The vector
//	@return The squared length of the vector
double		vlength2(t_vector3 v);

//	vadd: Add two vectors
//	@param v The first vector
//	@param u The second vector
//	@return The sum of the two vectors
t_vector3	vadd(t_vector3 v, t_vector3 u);

//	vsub: Subtract two vectors
//	@param v The first vector
//	@param u The second vector
//	@return The difference of the two vectors
t_vector3	vsub(t_vector3 v, t_vector3 u);

//	vmul: Multiply a vector by a scalar
//	@param v The vector
//	@param scalar The scalar
//	@return The product of the vector and the scalar
t_vector3	vmul(t_vector3 v, double scalar);

//	vdiv: Divide a vector by a scalar
//	@param v The vector
//	@param scalar The scalar
//	@return The quotient of the vector and the scalar
t_vector3	vdiv(t_vector3 v, double scalar);

//	vdot: Get the dot product of two vectors
//	@param v The first vector
//	@param u The second vector
//	@return The dot product of the two vectors
double		vdot(t_vector3 v, t_vector3 u);

//	vcross: Get the cross product of two vectors
//	@param v The first vector
//	@param u The second vector
//	@return The cross product of the two vectors
t_vector3	vcross(t_vector3 v, t_vector3 u);

//	vnormalized: Normalize a vector
//	@param v The vector
//	@return The normalized vector
t_vector3	vnormalized(t_vector3 v);

//	vnormalize: Normalize a vector
//	@param v The vector
//	@return The normalized vector
t_vector3	*vnormalize(t_vector3 *v);

#endif
