/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 10:51:29 by anpollan          #+#    #+#             */
/*   Updated: 2025/11/24 12:18:33 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	(*new_translation_matrix4(float scale_x, float scale_y, float scale_z))[4]
{
	float	(*translation)[4];
	int		i;
	int		j;

	translation = ft_calloc(1, sizeof(float) * 16);
	if (!translation)
		return (NULL);
	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			if (i == j)
				translation[i][j] = 1;
			else if (j == 3)
			{
				if (i == 0)
					translation[i][j] = scale_x;
				else if (i == 1)
					translation[i][j] = scale_y;
				else if (i == 2)
					translation[i][j] = scale_z;
			}
		}
	}
	return (translation);
}

float	(*new_scaling_matrix4(float scale_x, float scale_y, float scale_z))[4]
{
	float	(*scalar)[4];

	scalar	= ft_calloc(1, sizeof(float) * 16);
	if (!scalar)
		return (NULL);
	scalar[0][0] = scale_x;
	scalar[1][1] = scale_y;
	scalar[2][2] = scale_z;
	scalar[3][3] = 1;
	return (scalar);
}

float	(*shearing_matrix4(t_shear *shear))[4]
{
	float	(*shearing)[4];

	if (!shear)
		return (NULL);
	shearing = ft_calloc(1, sizeof(float) * 16);
	if (!shearing)
		return (NULL);
	shearing[0][0] = 1;
	shearing[0][1] = shear->xy;
	shearing[0][2] = shear->xz;
	shearing[1][0] = shear->yx;
	shearing[1][1] = 1;
	shearing[1][2] = shear->yz;
	shearing[2][0] = shear->zx;
	shearing[2][1] = shear->zy;
	shearing[2][2] = 1;
	shearing[3][3] = 1;
	return (shearing);
}
