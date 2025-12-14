/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhana <juhana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 17:00:05 by anpollan          #+#    #+#             */
/*   Updated: 2025/12/12 13:47:53 by juhana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	is_shadowed(t_world *w, t_point p)
{
	t_vector		v;
	float			distance;
	t_ray			r;
	t_intersections	*xs;
	t_intersection	h;
	
	v = tuple_subtract(w->light->position, p);
	distance = vector_magnitude(v);
	r = ray(p, normalize(v));
	xs = intersect_world(w, r);
	h = hit(xs);
	free_intersections(xs);
	if (h.t != FLT_MAX && h.t < distance)
		return (true);
	else
		return (false);
}

t_color	shade_hit(t_world *w, t_computations comps)
{
	if (!w)
		return (t_color){0, 0, 0};
	if (is_shadowed(w, comps.point) == true)
		w->light->in_shadow = true;
	return (lighting_test(comps, w->light));
	// return (lighting(comps.object, w->light, comps.point, comps.eyev));
}

t_color	color_at(t_world *w, t_ray r)
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
	comps = prepare_computations(x, r);
	free_intersections(xs);
	return (shade_hit(w, comps));
}
