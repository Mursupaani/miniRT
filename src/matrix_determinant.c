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

float	matrix2_determinant(t_matrix2 matrix)
{
	return (matrix.data[0][0] * matrix.data[1][1]
			- matrix.data[0][1] * matrix.data[1][0]);
}

float	matrix3_determinant(t_matrix3 matrix)
{
	float	result;
	int		i;

	result = 0;
	i = -1;
	while (++i < 3)
		result += matrix.data[0][i] * matrix3_cofactor(matrix, 0, i);
	return (result);
}

float	matrix4_determinant(t_matrix4 matrix)
{
	float	result;
	int		i;

	result = 0;
	i = -1;
	while (++i < 4)
		result += matrix.data[0][i] * matrix4_cofactor(matrix, 0, i);
	return (result);
}
