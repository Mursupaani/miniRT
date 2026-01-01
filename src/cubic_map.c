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

static t_face_layout	get_face_offset(t_cube_face face)
{
	if (face == UP)
		return ((t_face_layout){1, 2});
	else if (face == LEFT)
		return ((t_face_layout){0, 1});
	else if (face == FRONT)
		return ((t_face_layout){1, 1});
	else if (face == RIGHT)
		return ((t_face_layout){2, 1});
	else if (face == BACK)
		return ((t_face_layout){3, 1});
	else
		return ((t_face_layout){1, 0});
}

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

t_uv_map	cubic_atlas_map(t_point p)
{
	t_face_layout	offset;
	t_uv_map		uv;
	double			global_u;
	double			global_v;

	uv = cubic_map(p);
	offset = get_face_offset(uv.face);
	global_u = uv.u / 4;
	global_u += (double)offset.col / 4.0;
	global_v = uv.v / 3;
	global_v += (double)offset.row / 3.0;
	return ((t_uv_map){global_u, global_v, UP});
}
