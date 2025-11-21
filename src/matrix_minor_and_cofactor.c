/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_minor_and_cofactor.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 17:52:35 by anpollan          #+#    #+#             */
/*   Updated: 2025/11/20 18:52:47 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	matrix3_minor(float (*matrix)[3], int row, int column)
{
	float	(*submatrix)[2];
	float	minor;

	if (!matrix)
		return (FLT_MAX);
	if (row > 2 || row < 0 || column > 2 || column < 0)
	{
		ft_fprintf(STDERR_FILENO, "Dimensions are outside of 3x3 matrix.");
		return (FLT_MAX);
	}
	submatrix = matrix3_submatrix(matrix, row, column);
	minor = matrix2_determinant(submatrix);
	free(submatrix);
	return (minor);
}

float	matrix3_cofactor(float (*matrix)[3], int row, int column)
{
	float	minor;

	minor = matrix3_minor(matrix, row, column);
	if ((row + column) % 2 == 0)
		return (minor);
	else
		return (-minor);
}

float	matrix4_minor(float (*matrix)[4], int row, int column)
{
	float	(*submatrix)[3];
	float	minor;

	if (!matrix)
		return (FLT_MAX);
	if (row > 3 || row < 0 || column > 3 || column < 0)
	{
		ft_fprintf(STDERR_FILENO, "Dimensions are outside of 4x4 matrix.");
		return (FLT_MAX);
	}
	submatrix = matrix4_submatrix(matrix, row, column);
	minor = matrix3_determinant(submatrix);
	free(submatrix);
	return (minor);
}

float	matrix4_cofactor(float (*matrix)[4], int row, int column)
{
	float	minor;

	minor = matrix4_minor(matrix, row, column);
	if ((row + column) % 2 == 0)
		return (minor);
	else
		return (-minor);
}
