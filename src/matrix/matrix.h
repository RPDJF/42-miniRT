/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 22:51:30 by rude-jes          #+#    #+#             */
/*   Updated: 2024/10/28 22:51:31 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

# include "../vectors/vectors.h"

typedef struct s_matrix4
{
	double	data[4][4];
}	t_matrix4;

typedef struct s_matrix3
{
	double	data[3][3];
}	t_matrix3;

typedef enum e_axis
{
	X_AXIS = 0,
	Y_AXIS = 1,
	Z_AXIS = 2
}	t_axis;

typedef struct s_shearing
{
	double	xy;
	double	xz;
	double	yx;
	double	yz;
	double	zx;
	double	zy;
}	t_shearing;

// m4default: Get the default matrix
// @return The default matrix
t_matrix4	m4default(void);
// m4mul: Multiply two matrices
// @param m The first matrix
// @param n The second matrix
// @return The multiplied matrix
t_matrix4	m4mul(t_matrix4 m, t_matrix4 n);
//  m4mulv: Multiply a matrix by a vector
//  @param m The matrix
//  @param v The tuple
//  @return The multiplied tuple
t_tuple4	tm4mul(t_matrix4 m, t_tuple4 t);
//  m4transpose: Invert columns and rows of a matrix
//  @param m The matrix
//  @return The rotated matrix
t_matrix4	m4transpose(t_matrix4 m);
//  m3subm: Get the t_matrix3 submatrix of a t_matrix4
//  @param m The matrix
//  @param row The row to remove
//  @param col The column to remove
//  @return The submatrix
t_matrix3	m3subm(t_matrix4 m, int row, int col);
//	m3det: Get the determinant of a t_matrix3
//	@param m The matrix
//	@return The determinant
double		m3det(t_matrix3 m);
//	m4minor: Get the minor of a t_matrix4
//	@param m The matrix
//	@param row The row to remove
//	@param col The column to remove
//	@return The minor
double		m4minor(t_matrix4 m, int row, int col);
//	m4cofactor: Get the cofactor of a t_matrix4
//	@param m The matrix
//	@param row The row to remove
//	@param col The column to remove
double		m4cofactor(t_matrix4 m, int row, int col);
//	m4det: Get the determinant of a t_matrix4
//	@param m The matrix
//	@return The determinant
double		m4det(t_matrix4 m);
//	m4invert: Get the inverse of a t_matrix4
//	@param m The matrix
//	@param status The status of the inversion
//	@return The inverted matrix
t_matrix4	m4invert(t_matrix4 m, int *status);
//	m4translation: Get the translation matrix of a tuple
//	@param t The tuple containing the translation values
//	@return The translation matrix
t_matrix4	m4translation(t_tuple4 t);
//	m4scaling: Get the scaling matrix of a tuple
//	@param t The tuple containing the scaling values
//	@return The scaling matrix
t_matrix4	m4scaling(t_tuple4 t);
//	m4rotating: Get the rotation matrix of a given angle and axis
//	@param radian The angle in radian
//	@param axis The axis to rotate
//	@return The rotation matrix
t_matrix4	m4rotating(double radian, t_axis axis);
//	m4shearing: Get the shearing matrix of a t_shearing
//	@param sh The shearing values
//	@return The shearing matrix
t_matrix4	m4shearing(t_shearing sh);
//	m4rodrig_rot: Get the Rodrigues rotation matrix of a
//	vector and an angle
//	@param a The vector
//	@param angle The angle
//	@return The Rodrigues rotation matrix
t_matrix4	m4rodrig_rot(t_vector3 a, double angle);
//	m4rotating_dir: Get the rotation matrix of a vector
//	@note This function uses Rodrigues' rotation formula
//	@param from The vector to rotate
//	@param to The vector to rotate to
t_matrix4	m4rotating_dir(t_vector3 from, t_vector3 to);

#endif
