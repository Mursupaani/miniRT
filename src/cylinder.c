/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 12:34:14 by anpollan          #+#    #+#             */
/*   Updated: 2025/12/21 16:57:36 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static bool	check_cap(t_ray local_ray, double t)
{
	double	x;
	double	z;

	x = local_ray.origin.x + t * local_ray.direction.x;
	z = local_ray.origin.z + t * local_ray.direction.z;
	return ((x * x + z * z) <= 1);
}

static t_intersections *intersect_caps(t_object *cylinder, t_ray local_ray, t_intersections *xs)
{
	double	t;

	if (cylinder->closed == false || doubles_are_equal(local_ray.direction.y, 0))
		return (xs);
	t = (cylinder->minimum - local_ray.origin.y) / local_ray.direction.y;
	if (check_cap(local_ray, t))
		xs = add_intersection_to_intersections(intersection(t, cylinder), xs);
	t = (cylinder->maximum - local_ray.origin.y) / local_ray.direction.y;
	if (check_cap(local_ray, t))
		xs = add_intersection_to_intersections(intersection(t, cylinder), xs);
	return (xs);
}

static bool	intersection_within_limits(t_object *cylinder, double t, t_ray local_ray, int *xs_count)
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

static t_intersections	*calculate_hit_points(t_object *cylinder, double t0, double t1, t_ray local_ray)
{
	t_intersections	*xs;
	int		xs_count;
	bool	add_t0;
	bool	add_t1;
	int		i;

	xs_count = 0;
	add_t0 = intersection_within_limits(cylinder, t0, local_ray, &xs_count);
	add_t1 = intersection_within_limits(cylinder, t1, local_ray, &xs_count);
	if (add_t0 == false && add_t1 == false)
		return (intersect_caps(cylinder, local_ray, NULL));
	xs = malloc(sizeof(t_intersections));
	if (!xs)
		return (NULL);
	xs->arr = malloc(sizeof(t_intersection) * xs_count);
	xs->count = xs_count;
	i = 0;
	if (add_t0)
		xs->arr[i++] = intersection(t0, cylinder);
	if (add_t1)
		xs->arr[i] = intersection(t1, cylinder);
	return (intersect_caps(cylinder, local_ray, xs));
}

t_intersections	*intersect_cylinder(t_object *cylinder, t_ray local_ray)
{
	double	a;
	double	b;
	double	disc;
	double	t0;
	double	t1;

	a = pow(local_ray.direction.x, 2) + pow(local_ray.direction.z, 2);
	if (doubles_are_equal(a, 0))
		return (intersect_caps(cylinder, local_ray, NULL));
	b = 2 * local_ray.origin.x * local_ray.direction.x + 2 * local_ray.origin.z * local_ray.direction.z;
	disc = pow(b, 2) - 4 * a
		* (pow(local_ray.origin.x, 2) + pow(local_ray.origin.z, 2) - 1);
	if (disc < 0)
		return (NULL);
	t0 = (-b - sqrt(disc)) / (2 * a);
	t1 = (-b + sqrt(disc)) / (2 * a);
	if (t0 > t1)
		swap_doubles(&t0, &t1);
	return (calculate_hit_points(cylinder, t0, t1, local_ray));
}

t_object	*cylinder_new(void)
{
	return (object_new(CYLINDER));
	// t_object	*cylinder;
	//
	// cylinder = ft_calloc(1, sizeof(t_object));
	// if (!cylinder)
	// 	return (NULL);
	// cylinder->type = CYLINDER;
	// cylinder->center = point(0, 0, 0);
	// cylinder->transform = matrix4_identity();
	// cylinder->inverse_transform = cylinder->transform;
	// cylinder->inverse_transpose = cylinder->transform;
	// cylinder->material = material();
	// // FIXME: cylinder dimensions?
	// cylinder->height = 1;
	// cylinder->diameter = 1;
	// return (cylinder);
}
