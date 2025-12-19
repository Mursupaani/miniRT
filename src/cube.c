/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 15:27:07 by anpollan          #+#    #+#             */
/*   Updated: 2025/12/19 17:20:52 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_intersections	*calculate_min_and_max(t_loc_intersect xt, t_loc_intersect yt, t_loc_intersect zt, t_object *cube)
{
	t_intersections		*xs;
	double	tmin;
	double	tmax;

	xs = malloc(sizeof(t_intersections));
	if (!xs)
		return (NULL);
	xs->arr = malloc(sizeof(t_intersection) * 2);
	if (!xs->arr)
		return (NULL);
	tmin = max_of_min_t(xt.min, yt.min, zt.min);
	tmax = min_of_max_t(xt.max, yt.max, zt.max);
	xs->count = 2;
	xs->arr[0] = intersection(tmin, cube);
	xs->arr[1] = intersection(tmax, cube);
	return (xs);
}

t_loc_intersect	check_axis(double origin, double direction)
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

t_intersections	*local_intersect(t_object *cube, t_ray ray)
{
	t_loc_intersect	xt;
	t_loc_intersect	yt;
	t_loc_intersect	zt;

	xt = check_axis(ray.origin.x, ray.direction.x);
	yt = check_axis(ray.origin.y, ray.direction.y);
	zt = check_axis(ray.origin.z, ray.direction.z);
	return (calculate_min_and_max(xt, yt, zt, cube));
}

t_object	*cube_new(void)
{
	t_object	*cube;

	cube = ft_calloc(1, sizeof(t_object));
	if (!cube)
		return (NULL);
	cube->type = CUBE;
	cube->center = point(0, 0, 0);
	cube->transform = matrix4_identity();
	cube->inverse_transform = cube->transform;
	cube->inverse_transpose = cube->transform;
	cube->material = material();
	// FIXME: Cube dimensions?
	cube->height = 2;
	cube->diameter = 2;
	return (cube);
}
