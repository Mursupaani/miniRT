/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 20:21:43 by anpollan          #+#    #+#             */
/*   Updated: 2025/12/26 23:36:24 by anpollan         ###   ########.fr       */
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

t_uv_align	uv_align_check(t_color main, t_color ul, t_color ur, t_color bl, t_color br)
{
	t_uv_align	align;

	align.main = main;
	align.ul = ul;
	align.ur = ur;
	align.bl = bl;
	align.br = br;
	return (align);
}

t_uv_ptrn	uv_align_check_pattern(void)
{
	t_uv_ptrn uv;

	uv.a = color(DBL_MIN, DBL_MIN, DBL_MIN);
	uv.b = color(DBL_MIN, DBL_MIN, DBL_MIN);
	uv.width = 0;
	uv.height = 0;
	uv.type = ALIGN_CHECK;
	uv.sides[UP].main = color(1, 1, 1);
	uv.sides[UP].ul = color(1, 0, 0);
	uv.sides[UP].ur = color(1, 1, 0);
	uv.sides[UP].bl = color(0, 1, 0);
	uv.sides[UP].br = color(0, 1, 1);
	return (uv);
}

t_uv_ptrn	cube_map(t_cube_align cube_align)
{
	t_uv_ptrn uv;

	uv.a = color(DBL_MIN, DBL_MIN, DBL_MIN);
	uv.b = color(DBL_MIN, DBL_MIN, DBL_MIN);
	uv.width = 0;
	uv.height = 0;
	uv.type = UV_CUBE;
	uv.sides[UP] = cube_align.up;
	uv.sides[DOWN] = cube_align.down;
	uv.sides[LEFT] = cube_align.left;
	uv.sides[RIGHT] = cube_align.right;
	uv.sides[FRONT] = cube_align.front;
	uv.sides[BACK] = cube_align.back;
	return (uv);
}
