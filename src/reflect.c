/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhana <juhana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 18:37:01 by anpollan          #+#    #+#             */
/*   Updated: 2025/12/16 16:05:21 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector	reflect(t_vector in, t_vector normal)
{
	double	scale;

	scale = 2 * dot(in, normal);
	return (tuple_subtract(in, tuple_scale_multiply(normal, scale)));
}

static t_color	calculate_color(
		t_object *obj, t_light *light, t_vector eyev, t_lighting l)
{
	l.effective_color = color_mix(l.color_at_point, light->intensity);
	l.ambient = color_multiply(l.effective_color, obj->material.ambient);
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
		l.color_at_point = pattern_at_shape(
				comps.object->material.pattern, comps.object, comps.over_point);
	else
		l.color_at_point = comps.object->material.color;
	if (comps.in_shadow == true)
	{
		l.effective_color = color_mix(l.color_at_point, light->intensity);
		l.ambient = color_multiply(
				l.effective_color, comps.object->material.ambient);
		return (l.ambient);
	}
	l.normalv = comps.normalv;
	l.lightv = normalize(tuple_subtract(light->position, comps.over_point));
	l.light_dot_normal = dot(l.lightv, l.normalv);
	return (calculate_color(comps.object, light, comps.eyev, l));
}

t_color	lighting_old(t_object *obj, t_light *light, t_point position, t_vector eyev)
{
	t_lighting	l;

	if (!obj || !light)
		return ((t_color){1, 1, 1});
	// if (light->in_shadow == true)
	// {
	// 	l.effective_color = color_mix(obj->material.color, light->intensity);
	// 	l.ambient = color_multiply(l.effective_color, obj->material.ambient);
	// 	return (l.ambient);
	// }
	l.normalv = normal_at(obj, position);
	l.lightv = normalize(tuple_subtract(light->position, position));
	l.light_dot_normal = dot(l.lightv, l.normalv);
	return (calculate_color(obj, light, eyev, l));
}
