/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 12:18:16 by anpollan          #+#    #+#             */
/*   Updated: 2025/11/24 17:40:28 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_matrix4	x_rotation(float radians)
{
	t_matrix4	rotation;

	ft_bzero(&rotation, sizeof(rotation));
	rotation.data[0][0] = 1;
	rotation.data[1][1] = cosf(radians);
	rotation.data[1][2] = -sinf(radians);
	rotation.data[2][1] = sinf(radians);
	rotation.data[2][2] = cosf(radians);
	rotation.data[3][3] = 1;
	return (rotation);
}

t_matrix4	y_rotation(float radians)
{
	t_matrix4	rotation;

	ft_bzero(&rotation, sizeof(rotation));
	rotation.data[0][0] = cosf(radians);
	rotation.data[0][2] = sinf(radians);
	rotation.data[1][1] = 1;
	rotation.data[2][0] = -sinf(radians);
	rotation.data[2][2] = cosf(radians);
	rotation.data[3][3] = 1;
	return (rotation);
}

t_matrix4	z_rotation(float radians)
{
	t_matrix4	rotation;

	ft_bzero(&rotation, sizeof(rotation));
	rotation.data[0][0] = cosf(radians);
	rotation.data[0][1] = -sinf(radians);
	rotation.data[1][0] = sinf(radians);
	rotation.data[1][1] = cosf(radians);
	rotation.data[2][2] = 1;
	rotation.data[3][3] = 1;
	return (rotation);
}
