#ifndef MATRIX_H
# define MATRIX_H

# include "../vectors/vectors.h"

typedef struct s_matrix4
{
	float	data[4][4];
}	t_matrix4;

typedef struct s_matrix3
{
	float	data[3][3];
}	t_matrix3;

typedef struct s_matrix2
{
	float	data[2][2];
}	t_matrix2;

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
//  m4identity: Get the identity matrix of a given matrix
//  @param m The matrix
//  @return The identity matrix
t_matrix4	m4identity(t_matrix4 m);
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
//  m2subm: Get the t_matrix2 submatrix of a t_matrix3
//  @param m The matrix
//  @param row The row to remove
//  @param col The column to remove
//  @return The submatrix
t_matrix2	m2subm(t_matrix3 m, int row, int col);
//  m3minor: Get the minor of a t_matrix3
//  @param m The matrix
//  @param row The row to remove
//  @param col The column to remove
//  @return The minor
float		m3minor(t_matrix3 m, int row, int col);
//	m2det: Get the determinant of a t_matrix2
//	@param m The matrix
//	@return The determinant
float		m2det(t_matrix2 m);
//	m3cofactor: Get the cofactor of a t_matrix3
//	@param m The matrix
//	@param row The row to remove
//	@param col The column to remove
//	@return The cofactor
float		m3cofactor(t_matrix3 m, int row, int col);
//	m3det: Get the determinant of a t_matrix3
//	@param m The matrix
//	@return The determinant
float		m3det(t_matrix3 m);
//	m4minor: Get the minor of a t_matrix4
//	@param m The matrix
//	@param row The row to remove
//	@param col The column to remove
//	@return The minor
float		m4minor(t_matrix4 m, int row, int col);
//	m4cofactor: Get the cofactor of a t_matrix4
//	@param m The matrix
//	@param row The row to remove
//	@param col The column to remove
float		*m4cofactor(t_matrix4 m, int row, int col);
//	m4det: Get the determinant of a t_matrix4
//	@param m The matrix
//	@return The determinant
float		m4det(t_matrix4 m);
//	m4invert: Get the inverse of a t_matrix4
//	@param m The matrix
//	@return The inverted matrix
t_matrix4	m4invert(t_matrix4 *m);

#endif
