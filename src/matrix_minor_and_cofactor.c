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

double	matrix3_minor(t_matrix3 matrix, int row, int column)
{
	t_matrix2	submatrix;
	double		minor;

	if (row > 2 || row < 0 || column > 2 || column < 0)
	{
		ft_fprintf(STDERR_FILENO, "Dimensions are outside of 3x3 matrix.");
		return (DBL_MAX);
	}
	submatrix = matrix3_submatrix(matrix, row, column);
	minor = matrix2_determinant(submatrix);
	return (minor);
}

double	matrix3_cofactor(t_matrix3 matrix, int row, int column)
{
	double	minor;

	minor = matrix3_minor(matrix, row, column);
	if ((row + column) % 2 == 0)
		return (minor);
	else
		return (-minor);
}

double	matrix4_minor(t_matrix4 matrix, int row, int column)
{
	t_matrix3	submatrix;
	double		minor;

	if (row > 3 || row < 0 || column > 3 || column < 0)
	{
		ft_fprintf(STDERR_FILENO, "Dimensions are outside of 4x4 matrix.");
		return (DBL_MAX);
	}
	submatrix = matrix4_submatrix(matrix, row, column);
	minor = matrix3_determinant(submatrix);
	return (minor);
}

double	matrix4_cofactor(t_matrix4 matrix, int row, int column)
{
	double	minor;

	minor = matrix4_minor(matrix, row, column);
	if ((row + column) % 2 == 0)
		return (minor);
	else
		return (-minor);
}
