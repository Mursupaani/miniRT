/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhana <juhana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 17:00:05 by anpollan          #+#    #+#             */
/*   Updated: 2026/01/16 20:42:54 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdatomic.h>

bool	is_shadowed(t_world *w, t_point p, atomic_int *err)
{
	t_vector		v;
	double			distance;
	t_ray			r;
	t_intersections	*xs;
	t_intersection	h;

	v = tuple_subtract(w->light->position, p);
	distance = vector_magnitude(v);
	r = ray(p, normalize(v));
	xs = intersect_world(w, r, err);
	h = hit(xs);
	free_intersections(&xs);
	if (h.t != DBL_MAX && h.t < distance)
		return (true);
	else
		return (false);
}

t_color	shade_hit(
		t_world *w, t_computations comps, int recursions, atomic_int *err)
{
	t_color		surface;
	t_color		reflected;
	t_color		refracted;
	t_color		sum;
	double		reflectance;

	if (!w)
	{
		*err = 1;
		return ((t_color){0, 0, 0});
	}
	if (is_shadowed(w, comps.over_point, err) == true)
		comps.shadowed = true;
	surface = lighting(comps, w->light);
	reflected = reflected_color(w, comps, recursions, err);
	refracted = refracted_color(w, comps, recursions, err);
	if (comps.object->material.reflective > 0
		&& comps.object->material.transparency > 0)
	{
		reflectance = schlick(comps);
		sum = color_sum(surface, color_multiply(reflected, reflectance));
		sum = color_sum(sum, color_multiply(refracted, 1 - reflectance));
		return (sum);
	}
	return (color_sum(color_sum(surface, reflected), refracted));
}

t_color	color_at(t_world *w, t_ray r, int recursions, atomic_int *err)
{
	t_intersections	*xs;
	t_intersection	x;
	t_computations	comps;

	xs = intersect_world(w, r, err);
	if (*err)
		return ((t_color){DBL_MIN, DBL_MIN, DBL_MIN});
	x = hit(xs);
	if (x.object == NULL)
	{
		free_intersections(&xs);
		return ((t_color){0, 0, 0});
	}
	comps = prepare_computations(x, r, xs, err);
	if (*err)
	{
		free_intersections(&xs);
		return ((t_color){DBL_MIN, DBL_MIN, DBL_MIN});
	}
	free_intersections(&xs);
	return (shade_hit(w, comps, recursions, err));
}
