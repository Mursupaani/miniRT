/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 20:21:43 by anpollan          #+#    #+#             */
/*   Updated: 2026/01/16 18:54:20 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// FIXME: Whole file not needed anymore

t_uv_align	uv_align_check(
		t_color main, t_color ul, t_color ur, t_color bl, t_color br)
{
	t_uv_align	align;

	align.main = main;
	align.ul = ul;
	align.ur = ur;
	align.bl = bl;
	align.br = br;
	return (align);
}

t_pattern	uv_align_check_pattern(void)
{
	t_pattern	ptrn;

	ptrn = create_pattern(MAP, color(DBL_MIN, DBL_MIN, DBL_MIN), color(DBL_MIN, DBL_MIN, DBL_MIN));
	ptrn.uv_pattern.width = 0;
	ptrn.uv_pattern.height = 0;
	ptrn.uv_pattern.type = UV_ALIGN_CHECK;
	ptrn.uv_pattern.align_cube_sides[UP].main = color(1, 1, 1);
	ptrn.uv_pattern.align_cube_sides[UP].ul = color(1, 0, 0);
	ptrn.uv_pattern.align_cube_sides[UP].ur = color(1, 1, 0);
	ptrn.uv_pattern.align_cube_sides[UP].bl = color(0, 1, 0);
	ptrn.uv_pattern.align_cube_sides[UP].br = color(0, 1, 1);
	return (ptrn);
}

t_pattern	uv_align_cube_pattern(void)
{
	t_pattern	cube_pattern;
	t_color		red = color(1, 0, 0);
	t_color		yellow = color(1, 1, 0);
	t_color		brown = color(1, 0.5, 0);
	t_color		green = color(0, 1, 0);
	t_color		cyan = color(0, 1, 1);
	t_color		blue = color(0, 0, 1);
	t_color		purple = color(1, 0, 1);
	t_color		white = color(1, 1, 1);

	cube_pattern = create_pattern(MAP, color(DBL_MIN, DBL_MIN, DBL_MIN), color(DBL_MIN, DBL_MIN, DBL_MIN));
	cube_pattern.type = MAP;
	cube_pattern.uv_pattern.type = UV_ALIGN_CUBE;
	cube_pattern.uv_pattern.align_cube_sides[LEFT] = uv_align_check(yellow, cyan, red, blue, brown);
	cube_pattern.uv_pattern.align_cube_sides[FRONT] = uv_align_check(cyan, red, yellow, brown, green);
	cube_pattern.uv_pattern.align_cube_sides[RIGHT] = uv_align_check(red, yellow, purple, green, white);
	cube_pattern.uv_pattern.align_cube_sides[BACK] = uv_align_check(green, purple, cyan, white, blue);
	cube_pattern.uv_pattern.align_cube_sides[UP] = uv_align_check(brown, cyan, purple, red, yellow);
	cube_pattern.uv_pattern.align_cube_sides[DOWN] = uv_align_check(purple, brown, green, blue, white);
	return (cube_pattern);
}
