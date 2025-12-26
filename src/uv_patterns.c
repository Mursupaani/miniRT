/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv_patterns.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 13:16:57 by anpollan          #+#    #+#             */
/*   Updated: 2025/12/26 20:54:39 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_pattern	texture_map(t_uv_ptrn ptrn, t_uv_map (*uv_map)(t_point))
{
	t_pattern	map;

	map = create_pattern(MAP, (t_color){0, 0, 0}, (t_color){0, 0, 0});
	map.texture_map.pattern = ptrn;
	map.texture_map.uv_map = uv_map;
	return (map);
}

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

t_color	uv_pattern_at(t_uv_ptrn ptrn, double u, double v)
{
	int	u2;
	int	v2;

	if (ptrn.type == ALIGN_CHECK)
		return (handle_align_check(ptrn.align, u, v));
	u2 = floor(u * ptrn.width);
	v2 = floor(v * ptrn.height);
	if ((int)(u2 + v2) % 2 == 0)
		return (ptrn.a);
	else
		return (ptrn.b);
}

t_color	handle_uv_pattern(t_pattern ptrn, t_point ptrn_point)
{
	t_uv_map	map;

	map = ptrn.texture_map.uv_map(ptrn_point);
	return (uv_pattern_at(ptrn.texture_map.pattern, map.u, map.v));
	// if (ptrn.texture_map.pattern.type == ALIGN_CHECK)
	// 	return (uv_pattern_at(ptrn.texture_map.pattern, map.u, map.v));
	// else
	// 	return (uv_pattern_at(ptrn.texture_map.pattern, map.u, map.v));
}
