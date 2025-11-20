/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   submatrices.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 17:01:44 by anpollan          #+#    #+#             */
/*   Updated: 2025/11/20 17:38:46 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	store_submatrix2_values(
			float matrix[3][3], float result[2][2], int row, int column)
{
	int		i;
	int		j;
	int		k;
	int		l;

	i = -1;
	k = 0;
	while (++i < 3)
	{
		if (i == row)
			continue ;
		j = -1;
		l = 0;
		while (++j < 3)
		{
			if (j == column)
				continue ;
			result[k][l] = matrix[i][j];
			l++;
		}
		k++;
	}
}

float	(*matrix3_submatrix(float matrix[3][3], int row, int column))[2]
{
	float	(*result)[2];

	if (!matrix)
		return (NULL);
	if (row > 2 || row < 0 || column > 2 || column < 0)
	{
		ft_fprintf(STDERR_FILENO, "Dimensions are outside of 3x3 matrix.");
		return (NULL);
	}
	result = malloc(sizeof(float) * 4);
	if (!result)
		return (NULL);
	store_submatrix2_values(matrix, result, row, column);
	return (result);
}

static void	store_submatrix3_values(
			float matrix[4][4], float result[3][3], int row, int column)
{
	int		i;
	int		j;
	int		k;
	int		l;

	i = -1;
	k = 0;
	while (++i < 4)
	{
		if (i == row)
			continue ;
		j = -1;
		l = 0;
		while (++j < 4)
		{
			if (j == column)
				continue ;
			result[k][l] = matrix[i][j];
			l++;
		}
		k++;
	}
}

float	(*matrix4_submatrix(float matrix[4][4], int row, int column))[3]
{
	float	(*result)[3];

	if (!matrix)
		return (NULL);
	if (row > 3 || row < 0 || column > 3 || column < 0)
	{
		ft_fprintf(STDERR_FILENO, "Dimensions are outside of 4x4 matrix.");
		return (NULL);
	}
	result = malloc(sizeof(float) * 9);
	if (!result)
		return (NULL);
	store_submatrix3_values(matrix, result, row, column);
	return (result);
}
