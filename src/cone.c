/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 12:14:36 by anpollan          #+#    #+#             */
/*   Updated: 2026/01/16 18:43:44 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static bool	intersection_within_limits(
		t_object *cone, double t, t_ray local_ray, int *xs_count)
{
	double	y;

	y = local_ray.origin.y + t * local_ray.direction.y;
	if (y > cone->minimum && y < cone->maximum)
	{
		(*xs_count)++;
		return (true);
	}
	return (false);
}

static t_intersections	*calculate_single_hit(
		t_object *cone, double t, t_ray local_ray)
{
	t_intersections	*xs;
	int				xs_count;
	bool			add_t;

	xs_count = 0;
	add_t = intersection_within_limits(cone, t, local_ray, &xs_count);
	if (add_t == false)
		return (intersect_cone_caps(cone, local_ray, NULL));
	xs = malloc(sizeof(t_intersections));
	if (!xs)
		return (NULL);
	xs->arr = malloc(sizeof(t_intersection) * 1);
	xs->count = xs_count;
	xs->arr[0] = intersection(t, cone);
	return (intersect_cone_caps(cone, local_ray, xs));
}

static t_intersections	*calculate_hit_points(
		t_object *cone, double t0, double t1, t_ray local_ray)
{
	t_intersections	*xs;
	int				xs_count;
	bool			add_t0;
	bool			add_t1;
	int				i;

	xs_count = 0;
	add_t0 = intersection_within_limits(cone, t0, local_ray, &xs_count);
	add_t1 = intersection_within_limits(cone, t1, local_ray, &xs_count);
	if (add_t0 == false && add_t1 == false)
		return (intersect_cone_caps(cone, local_ray, NULL));
	xs = malloc(sizeof(t_intersections));
	if (!xs)
		return (NULL);
	xs->arr = malloc(sizeof(t_intersection) * xs_count);
	xs->count = xs_count;
	i = 0;
	if (add_t0)
		xs->arr[i++] = intersection(t0, cone);
	if (add_t1)
		xs->arr[i] = intersection(t1, cone);
	return (intersect_cone_caps(cone, local_ray, xs));
}

t_intersections	*intersect_cone(t_object *cone, t_ray local_ray)
{
	t_coefs	coefs;
	double	disc;
	double	t0;
	double	t1;

	coefs = calculate_cone_coefs(local_ray);
	if (doubles_are_equal(coefs.a, 0))
	{
		if (doubles_are_equal(coefs.b, 0))
			return (intersect_cone_caps(cone, local_ray, NULL));
		t0 = -coefs.c / (2 * coefs.b);
		return (calculate_single_hit(cone, t0, local_ray));
	}
	disc = pow(coefs.b, 2) - 4 * coefs.a * coefs.c;
	if (disc < 0)
		return (NULL);
	t0 = (-coefs.b - sqrt(disc)) / (2 * coefs.a);
	t1 = (-coefs.b + sqrt(disc)) / (2 * coefs.a);
	if (t0 > t1)
		swap_doubles(&t0, &t1);
	return (calculate_hit_points(cone, t0, t1, local_ray));
}

t_object	*cone_new(void)
{
	return (object_new(CONE));
}
