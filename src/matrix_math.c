/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_math.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 13:46:19 by anpollan          #+#    #+#             */
/*   Updated: 2025/11/19 14:33:10 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static float	get_multiplication_result(
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

float	(*multiply_matrix_4s(float m1[4][4], float m2[4][4]))[4]
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
			result[i][j] = get_multiplication_result(i, j, m1, m2);
			j++;
		}
		i++;
	}
	return (result);
}
