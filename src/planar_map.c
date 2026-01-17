/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   planar_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 18:27:23 by anpollan          #+#    #+#             */
/*   Updated: 2026/01/17 16:31:40 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_uv_map	planar_map(t_point p)
{
	double	u;
	double	v;
	double	raw_u;
	double	raw_v;
	double	integer_part;

	raw_u = modf(p.x, &integer_part);
	raw_v = modf(p.z, &integer_part);
	if (raw_u >= 0)
		u = fmod(raw_u, 1);
	else
		u = fmod(1 + raw_u, 1);
	if (raw_v >= 0)
		v = fmod(raw_v, 1);
	else
		v = fmod(1 + raw_v, 1);
	return ((t_uv_map){u, v, UP});
}
