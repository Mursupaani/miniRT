/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 11:35:34 by anpollan          #+#    #+#             */
/*   Updated: 2026/01/16 20:49:55 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	reflected_color(
		t_scene *w, t_computations comps, int reflections, atomic_int *err)
{
	t_ray	reflect_ray;
	t_color	color;

	if (comps.object->material.reflective == 0 || reflections <= 0)
		return ((t_color){0, 0, 0});
	reflect_ray = ray(comps.over_point, comps.reflectv);
	color = color_at(w, reflect_ray, --reflections, err);
	return (color_multiply(color, comps.object->material.reflective));
}
