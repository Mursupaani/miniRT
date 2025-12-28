/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 20:21:43 by anpollan          #+#    #+#             */
/*   Updated: 2025/12/28 16:36:54 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
	uv.type = UV_ALIGN_CHECK;
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
	uv.type = UV_CUBE_PTRN;
	uv.sides[UP] = cube_align.up;
	uv.sides[DOWN] = cube_align.down;
	uv.sides[LEFT] = cube_align.left;
	uv.sides[RIGHT] = cube_align.right;
	uv.sides[FRONT] = cube_align.front;
	uv.sides[BACK] = cube_align.back;
	return (uv);
}
