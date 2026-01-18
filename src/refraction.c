/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refraction.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 15:31:20 by anpollan          #+#    #+#             */
/*   Updated: 2026/01/16 20:49:39 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	schlick(t_computations comps)
{
	double	cos;
	double	n;
	double	sin_2t;
	double	cos_t;
	double	r0;

	cos = dot(comps.eyev, comps.normalv);
	if (comps.n1 > comps.n2)
	{
		n = comps.n1 / comps.n2;
		sin_2t = n * n * (1 - cos * cos);
		if (sin_2t > 1)
			return (1);
		cos_t = sqrt(1 - sin_2t);
		cos = cos_t;
	}
	r0 = pow((comps.n1 - comps.n2) / (comps.n1 + comps.n2), 2);
	return (r0 + (1 - r0) * pow((1 - cos), 5));
}

static t_color	calculate_refracted_color(
		t_world *w, t_computations comps, int recursions, atomic_int *err)
{
	t_refraction	r;
	t_vector		direction;
	t_ray			refract_ray;
	t_color			c;

	r.n_ratio = comps.n1 / comps.n2;
	r.cos_i = dot(comps.eyev, comps.normalv);
	r.sin2_t = r.n_ratio * r.n_ratio * (1 - r.cos_i * r.cos_i);
	if (r.sin2_t > 1)
		return ((t_color){0, 0, 0});
	r.cos_t = sqrt(1 - r.sin2_t);
	direction = tuple_subtract(
			tuple_scale_multiply(comps.normalv,
				(r.n_ratio * r.cos_i - r.cos_t)),
			tuple_scale_multiply(comps.eyev, r.n_ratio));
	refract_ray = ray(comps.under_point, direction);
	c = color_at(w, refract_ray, recursions - 1, err);
	return (color_multiply(c, comps.object->material.transparency));
}

t_color	refracted_color(
		t_world *w, t_computations comps, int recursions, atomic_int *err)
{
	if (comps.object->material.transparency == 0)
		return ((t_color){0, 0, 0});
	if (recursions == 0)
		return ((t_color){0, 0, 0});
	return (calculate_refracted_color(w, comps, recursions, err));
}
