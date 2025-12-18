/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhana <juhana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 17:00:05 by anpollan          #+#    #+#             */
/*   Updated: 2025/12/17 19:35:14 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	is_shadowed(t_world *w, t_point p)
{
	t_vector		v;
	double			distance;
	t_ray			r;
	t_intersections	*xs;
	t_intersection	h;
	
	v = tuple_subtract(w->light->position, p);
	distance = vector_magnitude(v);
	r = ray(p, normalize(v));
	xs = intersect_world(w, r);
	h = hit(xs);
	free_intersections(xs);
	if (h.t != DBL_MAX && h.t < distance)
		return (true);
	else
		return (false);
}

t_color	shade_hit(t_world *w, t_computations comps, int recursions)
{
	t_color	surface;
	t_color	reflected;
	t_color	refracted;

	if (!w)
		return (t_color){0, 0, 0};
	if (is_shadowed(w, comps.over_point) == true)
		comps.shadowed = true;
	surface = lighting(comps, w->light);
	reflected = reflected_color(w, comps, recursions);
	refracted = refracted_color(w, comps, recursions);
	return (color_sum(color_sum(surface, reflected), refracted));
}

t_color	color_at(t_world *w, t_ray r, int reflections)
{
	t_intersections	*xs;
	t_intersection	x;
	t_computations	comps;

	xs = intersect_world(w, r);
	x = hit(xs);
	if (x.object == NULL)
	{
		free_intersections(xs);
		return ((t_color){0, 0, 0});
	}
	comps = prepare_computations(x, r, xs);
	free_intersections(xs);
	return (shade_hit(w, comps, reflections));
}
