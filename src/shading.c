/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 17:00:05 by anpollan          #+#    #+#             */
/*   Updated: 2025/12/10 18:29:37 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	shade_hit(t_world *w, t_computations comps)
{
	if (!w)
		return (t_color){0, 0, 0};
	return (lighting(comps.object, w->light, comps.point, comps.eyev));
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
