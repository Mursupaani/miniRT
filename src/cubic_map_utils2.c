/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubic_map_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 16:37:56 by anpollan          #+#    #+#             */
/*   Updated: 2025/12/28 16:38:16 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_uv_map	cube_uv_up(t_point p)
{
	double	u;
	double	v;

	// FIXME: Not like in book but gives correct test output
	u = fmod(p.x + 1, 2) / 2;
	v = fmod(1 - p.z, 2) / 2;
	return ((t_uv_map){u, v, UP});
}

t_uv_map	cube_uv_down(t_point p)
{
	double	u;
	double	v;

	// FIXME: Not like in book but gives correct test output
	u = fmod(p.x + 1, 2) / 2;
	v = fmod(p.z + 1, 2) / 2;
	return ((t_uv_map){u, v, DOWN});
}
