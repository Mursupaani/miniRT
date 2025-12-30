/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spherical_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 18:23:36 by anpollan          #+#    #+#             */
/*   Updated: 2025/12/25 18:33:16 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static	double get_v(t_point p)
{
	t_vector	vec;
	double		radius;
	double		phi;

	vec = vector(p.x, p.y, p.z);
	radius = vector_magnitude(vec);
	phi = acos(p.y / radius);
	return (1 - (phi / M_PI));
}

static	double get_u(t_point p)
{
	double	theta;
	double	raw_u;

	theta = atan2(p.x, p.z);
	raw_u = theta / (2 * M_PI);
	return (1 - (raw_u + 0.5));
}

t_uv_map	spherical_map(t_point p)
{
	double	u;
	double	v;

	u = get_u(p);
	v = get_v(p);
	return ((t_uv_map){u, v, UP});
}
