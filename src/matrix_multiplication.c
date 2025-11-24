/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_multiplication.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 13:46:19 by anpollan          #+#    #+#             */
/*   Updated: 2025/11/24 18:09:00 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static float	get_matrix_row_tuple_product(float m_row[4], t_tuple tuple)
{
	return (m_row[0] * tuple.x
		+ m_row[1] * tuple.y
		+ m_row[2] * tuple.z
		+ m_row[3] * tuple.w);
}

static float	get_row_column_product(
			int i, int j, t_matrix4 m1, t_matrix4 m2)
{
	float	result;
	int		k;

	result = 0;
	k = 0;
	while (k < 4)
	{
		result += m1.data[i][k] * m2.data[k][j];
		k++;
	}
	return (result);
}

t_matrix4	matrix4_multiply(t_matrix4 m1, t_matrix4 m2)
{
	t_matrix4	result;
	int		i;
	int		j;

	i = 0;
	ft_bzero(&result, sizeof(result));
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			result.data[i][j] = get_row_column_product(i, j, m1, m2);
			j++;
		}
		i++;
	}
	return (result);
}

t_tuple	matrix4_and_tuple_multiply(t_matrix4 matrix, t_tuple tuple)
{
	t_tuple	result;

	ft_bzero(&result, sizeof(result));
	result.x = get_matrix_row_tuple_product(matrix.data[0], tuple);
	result.y = get_matrix_row_tuple_product(matrix.data[1], tuple);
	result.z = get_matrix_row_tuple_product(matrix.data[2], tuple);
	result.w = get_matrix_row_tuple_product(matrix.data[3], tuple);
	return (result);
}
