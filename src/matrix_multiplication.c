/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_multiplication.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 13:46:19 by anpollan          #+#    #+#             */
/*   Updated: 2025/11/20 16:25:01 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static float	get_matrix_row_tuple_product(float m_row[4], t_tuple *tuple)
{
	return (m_row[0] * tuple->x
		+ m_row[1] * tuple->y
		+ m_row[2] * tuple->z
		+ m_row[3] * tuple->w);
}

static float	get_row_column_product(
			int i, int j, float m1[4][4], float m2[4][4])
{
	float	result;
	int		k;

	result = 0;
	k = 0;
	while (k < 4)
	{
		result += m1[i][k] * m2[k][j];
		k++;
	}
	return (result);
}

float	(*matrix4_multiply(float m1[4][4], float m2[4][4]))[4]
{
	float	(*result)[4];
	int		i;
	int		j;

	if (!m1 && !m2)
		return (NULL);
	result = (float (*)[4])malloc(sizeof(float) * 16);
	if (!result)
		return (NULL);
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			result[i][j] = get_row_column_product(i, j, m1, m2);
			j++;
		}
		i++;
	}
	return (result);
}

t_tuple	matrix4_and_tuple_multiply(float (*matrix)[4], t_tuple *tuple)
{
	t_tuple	result;

	ft_bzero(&result, sizeof(t_tuple));
	if (!matrix)
		return (result);
	result.x = get_matrix_row_tuple_product(matrix[0], tuple);
	result.y = get_matrix_row_tuple_product(matrix[1], tuple);
	result.z = get_matrix_row_tuple_product(matrix[2], tuple);
	result.w = get_matrix_row_tuple_product(matrix[3], tuple);
	return (result);
}
