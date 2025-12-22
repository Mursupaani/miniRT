/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaaskel <jjaaskel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 12:18:16 by anpollan          #+#    #+#             */
/*   Updated: 2025/12/22 14:45:15 by jjaaskel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_matrix4	rotation_matrix_from_orientation(t_vector orientation)
{
	t_vector	o;
	double		angle_x;
	double		angle_y;

	o = normalize(orientation);
	angle_x = acos(o.y);
	angle_y = atan2(o.x, o.z);
	return (matrix4_multiply(rotation_y(angle_y), rotation_x(angle_x)));
}

t_matrix4	rotation_x(double radians)
{
	t_matrix4	rotation;

	ft_bzero(&rotation, sizeof(rotation));
	rotation.data[0][0] = 1;
	rotation.data[1][1] = cos(radians);
	rotation.data[1][2] = -sin(radians);
	rotation.data[2][1] = sin(radians);
	rotation.data[2][2] = cos(radians);
	rotation.data[3][3] = 1;
	return (rotation);
}

t_matrix4	rotation_y(double radians)
{
	t_matrix4	rotation;

	ft_bzero(&rotation, sizeof(rotation));
	rotation.data[0][0] = cos(radians);
	rotation.data[0][2] = sin(radians);
	rotation.data[1][1] = 1;
	rotation.data[2][0] = -sin(radians);
	rotation.data[2][2] = cos(radians);
	rotation.data[3][3] = 1;
	return (rotation);
}

t_matrix4	rotation_z(double radians)
{
	t_matrix4	rotation;

	ft_bzero(&rotation, sizeof(rotation));
	rotation.data[0][0] = cos(radians);
	rotation.data[0][1] = -sin(radians);
	rotation.data[1][0] = sin(radians);
	rotation.data[1][1] = cos(radians);
	rotation.data[2][2] = 1;
	rotation.data[3][3] = 1;
	return (rotation);
}
