/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubic_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 16:36:37 by anpollan          #+#    #+#             */
/*   Updated: 2025/12/28 16:37:36 by anpollan         ###   ########.fr       */
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

t_uv_map	cube_uv_left(t_point p)
{
	double	u;
	double	v;

	u = fmod(p.z + 1, 2) / 2;
	v = fmod(p.y + 1, 2) / 2;
	return ((t_uv_map){u, v});
}

t_uv_map	cube_uv_right(t_point p)
{
	double	u;
	double	v;

	u = fmod(1 - p.z, 2) / 2;
	v = fmod(p.y + 1, 2) / 2;
	return ((t_uv_map){u, v});
}
