/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_inversion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 18:53:32 by anpollan          #+#    #+#             */
/*   Updated: 2025/11/20 19:07:36 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	(*matrix4_invert(float (*matrix)[4]))[4]
{
	float	(*invert)[4];
	int		i;
	int		j;
	float	determinant;

	if (!matrix)
		return (NULL);
	determinant = matrix4_determinant(matrix);
	if (determinant == 0)
		return (NULL);
	invert = malloc(sizeof(float) * 16);
	if (!invert)
		return (NULL);
	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
			invert[j][i] = matrix4_cofactor(matrix, i, j) / determinant;
	}
	return (invert);
}
