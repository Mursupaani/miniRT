/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   submatrices.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 17:01:44 by anpollan          #+#    #+#             */
/*   Updated: 2025/11/24 18:09:39 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	store_submatrix2_values(
			t_matrix3 matrix, t_matrix2 *result, int row, int column)
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
			result->data[k][l] = matrix.data[i][j];
			l++;
		}
		k++;
	}
}

t_matrix2	matrix3_submatrix(t_matrix3 matrix, int row, int column)
{
	t_matrix2	result;

	ft_bzero(&result, sizeof(result));
	if (row > 2 || row < 0 || column > 2 || column < 0)
	{
		ft_fprintf(STDERR_FILENO, "Dimensions are outside of 3x3 matrix.");
		return (result);
	}
	store_submatrix2_values(matrix, &result, row, column);
	return (result);
}

static void	store_submatrix3_values(
			t_matrix4 matrix, t_matrix3 *result, int row, int column)
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
			result->data[k][l] = matrix.data[i][j];
			l++;
		}
		k++;
	}
}

t_matrix3	matrix4_submatrix(t_matrix4 matrix, int row, int column)
{
	t_matrix3	result;

	ft_bzero(&result, sizeof(result));
	if (row > 3 || row < 0 || column > 3 || column < 0)
	{
		ft_fprintf(STDERR_FILENO, "Dimensions are outside of 4x4 matrix.");
		return (result);
	}
	store_submatrix3_values(matrix, &result, row, column);
	return (result);
}
