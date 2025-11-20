/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_transpose.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 16:07:02 by anpollan          #+#    #+#             */
/*   Updated: 2025/11/20 16:24:02 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	(*matrix4_transpose(float (*matrix)[4]))[4]
{
	float	(*result)[4];
	int		i;
	int		j;

	if (!matrix)
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
			result[j][i] = matrix[i][j];
			j++;
		}
		i++;
	}
	return (result);
}
