/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 12:18:16 by anpollan          #+#    #+#             */
/*   Updated: 2025/11/24 12:39:08 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	(*new_x_rotation_matrix4(float radians))[4]
{
	float	(*rotation)[4];

	rotation = ft_calloc(1, sizeof(float) * 16);
	if (!rotation)
		return (NULL);
	rotation[0][0] = 1;
	rotation[1][1] = cosf(radians);
	rotation[1][2] = -sinf(radians);
	rotation[2][1] = sinf(radians);
	rotation[2][2] = cosf(radians);
	rotation[3][3] = 1;
	return (rotation);
}

float	(*new_y_rotation_matrix4(float radians))[4]
{
	float	(*rotation)[4];

	rotation = ft_calloc(1, sizeof(float) * 16);
	if (!rotation)
		return (NULL);
	rotation[0][0] = cosf(radians);
	rotation[0][2] = sinf(radians);
	rotation[1][1] = 1;
	rotation[2][0] = -sinf(radians);
	rotation[2][2] = cosf(radians);
	rotation[3][3] = 1;
	return (rotation);
}

float	(*new_z_rotation_matrix4(float radians))[4]
{
	float	(*rotation)[4];

	rotation = ft_calloc(1, sizeof(float) * 16);
	if (!rotation)
		return (NULL);
	rotation[0][0] = cosf(radians);
	rotation[0][1] = -sinf(radians);
	rotation[1][0] = sinf(radians);
	rotation[1][1] = cosf(radians);
	rotation[2][2] = 1;
	rotation[3][3] = 1;
	return (rotation);
}
