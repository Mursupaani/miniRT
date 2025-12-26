/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv_patterns.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 13:16:57 by anpollan          #+#    #+#             */
/*   Updated: 2025/12/25 20:57:45 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_pattern	texture_map(t_uv_ptrn ptrn, t_uv_map (*uv_map)(t_point))
{
	t_pattern	map;

	map = create_pattern(UV_PATTERN, (t_color){0, 0, 0}, (t_color){0, 0, 0});
	map.texture_map.pattern = ptrn;
	map.texture_map.uv_map = uv_map;
	return (map);
}

t_color	uv_pattern_at(t_uv_ptrn ptrn, double u, double v)
{
	int	u2;
	int	v2;

	u2 = floor(u * ptrn.width);
	v2 = floor(v * ptrn.height);
	if ((u2 + v2) % 2 == 0)
		return (ptrn.a);
	else
		return (ptrn.b);
}

t_color	handle_uv_pattern(t_pattern ptrn, t_point ptrn_point)
{
	t_uv_map	map;

	map = ptrn.texture_map.uv_map(ptrn_point);
	return (uv_pattern_at(ptrn.texture_map.pattern, map.u, map.v));
}
