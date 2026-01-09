/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_transform.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 18:36:30 by anpollan          #+#    #+#             */
/*   Updated: 2026/01/07 14:12:34 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_matrix4	add_orientation_values(
				t_vector left, t_vector true_up, t_vector forward)
{
	t_matrix4	orientation;

	ft_bzero(&orientation, sizeof(t_matrix4));
	orientation.data[0][0] = left.x;
	orientation.data[0][1] = left.y;
	orientation.data[0][2] = left.z;
	orientation.data[1][0] = true_up.x;
	orientation.data[1][1] = true_up.y;
	orientation.data[1][2] = true_up.z;
	orientation.data[2][0] = -forward.x;
	orientation.data[2][1] = -forward.y;
	orientation.data[2][2] = -forward.z;
	orientation.data[3][3] = 1;
	return (orientation);
}

t_matrix4	view_transform(t_point from, t_point to, t_vector up, t_camera *c)
{
	t_vector	forward;
	t_vector	left;
	t_vector	true_up;
	t_matrix4	orientation;

	if (c)
	{
		c->from = from;
		c->to = to;
		c->up = up;
	}
	forward = normalize(tuple_subtract(to, from));
	left = cross(forward, normalize(up));
	true_up = cross(left, forward);
	orientation = add_orientation_values(left, true_up, forward);
	return  (matrix4_multiply(orientation,
				translation_matrix4(-from.x, -from.y, -from.z)));
}
