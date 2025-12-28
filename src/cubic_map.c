/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubic_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 16:31:14 by anpollan          #+#    #+#             */
/*   Updated: 2025/12/28 16:35:47 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_cube_face	face_from_point(t_point p)
{
	double	coord;

	coord = max_absolute_coord_component(p.x, p.y, p.z);
	if (coord == p.x)
		return (RIGHT);
	else if (coord == -p.x)
		return (LEFT);
	else if (coord == p.y)
		return (UP);
	else if (coord == -p.y)
		return (DOWN);
	else if (coord == p.z)
		return (FRONT);
	return (BACK);
}

t_uv_map	cubic_map(t_point p)
{
	t_cube_face	face;

	face = face_from_point(p);
	if (face == UP)
		return (cube_uv_up(p));
	else if (face == DOWN)
		return (cube_uv_down(p));
	else if (face == LEFT)
		return (cube_uv_left(p));
	else if (face == RIGHT)
		return (cube_uv_right(p));
	else if (face == FRONT)
		return (cube_uv_front(p));
	else
		return (cube_uv_back(p));
}
