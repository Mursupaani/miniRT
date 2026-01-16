/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 15:27:07 by anpollan          #+#    #+#             */
/*   Updated: 2026/01/16 18:55:38 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_intersections	*calculate_min_and_max(
		t_loc_intersect xt, t_loc_intersect yt,
		t_loc_intersect zt, t_object *cube)
{
	t_intersections		*xs;
	double				tmin;
	double				tmax;

	tmin = max_of_min_t(xt.min, yt.min, zt.min);
	tmax = min_of_max_t(xt.max, yt.max, zt.max);
	if (tmin > tmax)
		return (NULL);
	xs = malloc(sizeof(t_intersections));
	if (!xs)
		return (NULL);
	xs->arr = malloc(sizeof(t_intersection) * 2);
	if (!xs->arr)
		return (NULL);
	xs->count = 2;
	xs->arr[0] = intersection(tmin, cube);
	xs->arr[1] = intersection(tmax, cube);
	return (xs);
}

static t_loc_intersect	check_axis(double origin, double direction)
{
	double				tmin_numerator;
	double				tmax_numerator;
	double				tmin;
	double				tmax;

	tmin_numerator = -1 - origin;
	tmax_numerator = 1 - origin;
	if (fabs(direction) >= EPSILON)
	{
		tmin = tmin_numerator / direction;
		tmax = tmax_numerator / direction;
	}
	else
	{
		tmin = tmin_numerator * INFINITY;
		tmax = tmax_numerator * INFINITY;
	}
	if (tmin > tmax)
		swap_doubles(&tmin, &tmax);
	return ((t_loc_intersect){tmin, tmax});
}

t_intersections	*intersect_cube(t_object *cube, t_ray local_ray)
{
	t_loc_intersect	xt;
	t_loc_intersect	yt;
	t_loc_intersect	zt;

	xt = check_axis(local_ray.origin.x, local_ray.direction.x);
	yt = check_axis(local_ray.origin.y, local_ray.direction.y);
	zt = check_axis(local_ray.origin.z, local_ray.direction.z);
	return (calculate_min_and_max(xt, yt, zt, cube));
}

t_object	*cube_new(void)
{
	return (object_new(CUBE));
}
