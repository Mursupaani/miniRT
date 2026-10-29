/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv_patterns.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 13:16:57 by anpollan          #+#    #+#             */
/*   Updated: 2026/01/16 20:35:32 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_color	handle_align_check(t_uv_align align, double u, double v)
{
	if (v > 0.8)
	{
		if (u < 0.2)
			return (align.ul);
		if (u > 0.8)
			return (align.ur);
	}
	else if (v < 0.2)
	{
		if (u < 0.2)
			return (align.bl);
		if (u > 0.8)
			return (align.br);
	}
	return (align.main);
}

static t_color	uv_texture_at(mlx_texture_t *texture, double u, double v)
{
	int	x;
	int	y;

	v = 1 - v;
	x = round(u * (texture->width - 1));
	y = round(v * (texture->height - 1));
	return (pixel_at(texture, x, y));
}

static t_color	handle_uv_checkers_texture(t_pattern ptrn, double u, double v)
{
	int	u2;
	int	v2;

	u2 = floor(u * ptrn.uv_pattern.width);
	v2 = floor(v * ptrn.uv_pattern.height);
	if ((u2 + v2) % 2 == 0)
		return (ptrn.a);
	else
		return (ptrn.b);
}

static t_color	uv_pattern_at(t_pattern ptrn, t_uv_map uv)
{
	if (ptrn.uv_pattern.type != UV_CHECKERS)
		return (handle_align_check(
				ptrn.uv_pattern.align_cube_sides[uv.face], uv.u, uv.v));
	else
		return (handle_uv_checkers_texture(ptrn, uv.u, uv.v));
}

t_color	handle_uv_pattern(t_pattern ptrn, t_point ptrn_point)
{
	t_uv_map	uv;

	uv = ptrn.uv_pattern.uv_map(ptrn_point);
	if (ptrn.uv_pattern.type == UV_TEXTURE
		|| ptrn.uv_pattern.type == UV_CUBE_TEXTURE)
		return (uv_texture_at(ptrn.uv_pattern.textures[UP], uv.u, uv.v));
	else
		return (uv_pattern_at(ptrn, uv));
}
