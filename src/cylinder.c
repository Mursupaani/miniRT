/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 18:59:34 by anpollan          #+#    #+#             */
/*   Updated: 2026/01/16 19:03:05 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static bool	intersection_within_limits(
		t_object *cylinder, double t, t_ray local_ray, int *xs_count)
{
	double	y;

	y = local_ray.origin.y + t * local_ray.direction.y;
	if (y > cylinder->minimum && y < cylinder->maximum)
	{
		(*xs_count)++;
		return (true);
	}
	return (false);
}

static t_intersections	*calculate_hit_points(
		t_object *cylinder, t_t_vals ts, t_ray local_ray, atomic_int *err)
{
	t_intersections	*xs;
	int				xs_count;
	bool			add_t0;
	bool			add_t1;
	int				i;

	xs_count = 0;
	add_t0 = intersection_within_limits(cylinder, ts.t0, local_ray, &xs_count);
	add_t1 = intersection_within_limits(cylinder, ts.t1, local_ray, &xs_count);
	if (add_t0 == false && add_t1 == false)
		return (intersect_cylinder_caps(cylinder, local_ray, NULL, err));
	xs = malloc_intersections(xs_count, err);
	if (*err)
		return (NULL);
	xs->count = xs_count;
	i = 0;
	if (add_t0)
		xs->arr[i++] = intersection(ts.t0, cylinder);
	if (add_t1)
		xs->arr[i] = intersection(ts.t1, cylinder);
	return (intersect_cylinder_caps(cylinder, local_ray, xs, err));
}

t_intersections	*intersect_cylinder(
		t_object *cylinder, t_ray local_ray, atomic_int *err)
{
	t_coefs		coefs;
	double		disc;
	t_t_vals	ts;

	coefs.a = pow(local_ray.direction.x, 2) + pow(local_ray.direction.z, 2);
	if (doubles_are_equal(coefs.a, 0))
		return (intersect_cylinder_caps(cylinder, local_ray, NULL, err));
	coefs.b = 2 * local_ray.origin.x * local_ray.direction.x + 2
		* local_ray.origin.z * local_ray.direction.z;
	coefs.c = (pow(local_ray.origin.x, 2) + pow(local_ray.origin.z, 2) - 1);
	disc = pow(coefs.b, 2) - 4 * coefs.a * coefs.c;
	if (disc < 0)
		return (NULL);
	ts.t0 = (-coefs.b - sqrt(disc)) / (2 * coefs.a);
	ts.t1 = (-coefs.b + sqrt(disc)) / (2 * coefs.a);
	if (ts.t0 > ts.t1)
		swap_doubles(&ts.t0, &ts.t1);
	return (calculate_hit_points(cylinder, ts, local_ray, err));
}

t_object	*cylinder_new(void)
{
	return (object_new(CYLINDER));
}
