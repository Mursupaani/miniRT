/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 18:37:01 by anpollan          #+#    #+#             */
/*   Updated: 2025/12/10 18:43:16 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector	reflect(t_vector in, t_vector normal)
{
	float	scale;

	scale = 2 * dot(in, normal);
	return (tuple_subtract(in, tuple_scale_multiply(normal, scale)));
}

static t_color	calculate_color(
		t_object *obj, t_light *light, t_vector eyev, t_lighting l)
{
	l.effective_color = color_mix(obj->material.color, light->intensity);
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
			l.factor = powf(l.reflect_dot_eye, obj->material.shininess);
			l.specular = color_multiply(color_multiply(
						light->intensity, obj->material.specular), l.factor);
		}
	}
	return (color_sum(color_sum(l.ambient, l.diffuse), l.specular));
}

t_color	lighting(t_object *obj, t_light *light, t_point position, t_vector eyev)
{
	t_lighting	l;

	if (!obj || !light)
		return ((t_color){1, 1, 1});
	l.normalv = normal_at(obj, position);
	l.lightv = normalize(tuple_subtract(light->position, position));
	l.light_dot_normal = dot(l.lightv, l.normalv);
	return (calculate_color(obj, light, eyev, l));
}

// t_color	lighting_bu(
// t_object *obj, t_light *light, t_point position, t_vector eyev)
// {
// 	t_vector	normalv;
// 	t_vector	lightv;
// 	float		light_dot_normal;
// 	t_vector	reflectv;
// 	float		reflect_dot_eye;
// 	float		factor;
// 	t_color		ambient;
// 	t_color		effective_color;
// 	t_color		diffuse;
// 	t_color		specular;
//
// 	if (!obj || !light)
// 		return ((t_color){1, 1, 1});
// 	normalv = normal_at(obj, position);
// 	effective_color = color_mix(obj->material.color, light->intensity);
// 	lightv = vector_normalize(tuple_subtract(light->position, position));
// 	ambient = color_multiply(effective_color, obj->material.ambient);
// 	light_dot_normal = dot(lightv, normalv);
// 	if (light_dot_normal < 0)
// 	{
// 		diffuse = (t_color){0, 0, 0};
// 		specular = (t_color){0, 0, 0};
// 	}
// 	else
// 	{
// 		diffuse = color_multiply(
// 				color_multiply(effective_color, obj->material.diffuse),
// 				light_dot_normal);
// 		reflectv = reflect(tuple_negate(lightv), normalv);
// 		reflect_dot_eye = dot(reflectv, eyev);
// 		if (reflect_dot_eye <= 0)
// 			specular = (t_color){0, 0, 0};
// 		else
// 		{
// 			factor = powf(reflect_dot_eye, obj->material.shininess);
// 			specular = color_multiply(
// 				color_multiply(light->intensity, obj->material.specular),
// 				factor);
// 		}
// 	}
// 	return (color_sum(color_sum(ambient, diffuse), specular));
// }
//
