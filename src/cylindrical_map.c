/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylindrical_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 19:02:42 by anpollan          #+#    #+#             */
/*   Updated: 2025/12/26 20:39:10 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static double	get_u(t_point p)
{
	double	theta;
	double	raw_u;

	theta = atan2(p.x, p.z);
	raw_u = theta / (2 * M_PI);
	return (1 - (raw_u + 0.5));
}

static double	get_v(t_point p)
{
	double	raw_v;
	double	integer_part;

	raw_v = modf(p.y, &integer_part);
	// FIXME: No need to check? Just use the fmod?
	if (raw_v >= 0)
		return (fmod(raw_v, 1));
	else
		return (fmod(1 + raw_v, 1));
}

t_uv_map	cylindrical_map(t_point p)
{
	double	u;
	double	v;

	u = get_u(p);
	v = get_v(p);
	return ((t_uv_map){u, v});
}
