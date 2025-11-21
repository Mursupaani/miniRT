/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_determinant.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 16:53:20 by anpollan          #+#    #+#             */
/*   Updated: 2025/11/20 18:49:49 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	matrix2_determinant(float matrix[2][2])
{
	if (!matrix)
		return (0);
	return (matrix[0][0] * matrix[1][1]
			- matrix[0][1] * matrix[1][0]);
}

float	matrix3_determinant(float matrix[3][3])
{
	float	result;
	int		i;

	if (!matrix)
		return (FLT_MAX);
	result = 0;
	i = -1;
	while (++i < 3)
		result += matrix[0][i] * matrix3_cofactor(matrix, 0, i);
	return (result);
}

float	matrix4_determinant(float matrix[4][4])
{
	float	result;
	int		i;

	if (!matrix)
		return (FLT_MAX);
	result = 0;
	i = -1;
	while (++i < 4)
		result += matrix[0][i] * matrix4_cofactor(matrix, 0, i);
	return (result);
}
