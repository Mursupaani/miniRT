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

bool	is_shadowed(t_scene *w, t_point p, atomic_int *err)
{
	t_vector		v;
	double			distance;
	t_ray			r;
	t_intersections	*xs;
	t_intersection	h;

	v = tuple_subtract(w->light->position, p);
	distance = vector_magnitude(v);
	r = ray(p, normalize(v));
	xs = intersect_scene(w, r, err);
	h = hit(xs);
	free_intersections(&xs);
	if (h.t != DBL_MAX && h.t < distance)
		return (true);
	else
		return (false);
}

t_color	shade_hit(
		t_scene *w, t_computations comps, int recursions, atomic_int *err)
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

t_color	color_at(t_scene *w, t_ray r, int recursions, atomic_int *err)
{
	t_intersections	*xs;
	t_intersection	x;
	t_computations	comps;

	xs = intersect_scene(w, r, err);
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

static t_color	calculate_color(
		t_object *obj, t_light *light, t_vector eyev, t_lighting l)
{
	l.effective_color = color_mix(l.color_at_point, light->intensity);
	l.ambient = color_multiply(color_mix(
				l.color_at_point, light->ambient_color), obj->material.ambient);
	if (l.light_dot_normal < 0)
	{
		l.diffuse = (t_color){0, 0, 0};
		l.specular = (t_color){0, 0, 0};
	}
	else
	{
		l.diffuse = color_multiply(color_multiply(
					l.effective_color, obj->material.diffuse),
				l.light_dot_normal);
		l.reflectv = reflect(tuple_negate(l.lightv), l.normalv);
		l.reflect_dot_eye = dot(l.reflectv, eyev);
		if (l.reflect_dot_eye <= 0)
			l.specular = (t_color){0, 0, 0};
		else
		{
			l.factor = pow(l.reflect_dot_eye, obj->material.shininess);
			l.specular = color_multiply(color_multiply(
						light->intensity, obj->material.specular), l.factor);
		}
	}
	return (color_sum(color_sum(l.ambient, l.diffuse), l.specular));
}

t_color	lighting(t_computations comps, t_light *light)
{
	t_lighting	l;

	if (!light)
		return ((t_color){1, 1, 1});
	if (comps.object->material.pattern.type != NONE)
	{
		l.color_at_point = pattern_at_shape(
				comps.object->material.pattern, comps.object, comps.over_point);
		l.color_at_point = color_mix(l.color_at_point,
				comps.object->material.color);
	}
	else
		l.color_at_point = comps.object->material.color;
	if (comps.shadowed == true)
	{
		l.effective_color = color_mix(l.color_at_point, light->ambient_color);
		l.ambient = color_multiply(
				l.effective_color, comps.object->material.ambient);
		return (l.ambient);
	}
	l.normalv = comps.normalv;
	l.lightv = normalize(tuple_subtract(light->position, comps.over_point));
	l.light_dot_normal = dot(l.lightv, l.normalv);
	return (calculate_color(comps.object, light, comps.eyev, l));
}
