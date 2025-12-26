/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubic_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 20:21:43 by anpollan          #+#    #+#             */
/*   Updated: 2025/12/26 23:35:14 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_uv_map	cube_uv_front(t_point p)
{
	double	u;
	double	v;

	u = fmod(p.x + 1, 2) / 2;
	v = fmod(p.y + 1, 2) / 2;
	return ((t_uv_map){u, v});
}

t_uv_map	cube_uv_back(t_point p)
{
	double	u;
	double	v;

	u = fmod(1 - p.x, 2) / 2;
	v = fmod(p.y + 1, 2) / 2;
	return ((t_uv_map){u, v});
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

t_uv_ptrn	uv_align_check(void)
{
	t_uv_ptrn uv;

	uv.a = color(DBL_MIN, DBL_MIN, DBL_MIN);
	uv.b = color(DBL_MIN, DBL_MIN, DBL_MIN);
	uv.width = 0;
	uv.height = 0;
	uv.type = ALIGN_CHECK;
	uv.align.main = color(1, 1, 1);
	uv.align.ul = color(1, 0, 0);
	uv.align.ur = color(1, 1, 0);
	uv.align.bl = color(0, 1, 0);
	uv.align.br = color(0, 1, 1);
	return (uv);
}
