/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 10:13:15 by anpollan          #+#    #+#             */
/*   Updated: 2025/12/05 19:14:11 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

t_light	*point_light(t_point position, t_color intensity)
{
	t_light	*point_light;

	point_light = ft_calloc(1, sizeof(t_light));
	if (!point_light)
		return (NULL);
	point_light->intensity = intensity;
	point_light->position = position;
	return (point_light);
}

t_color	lighting(t_object *obj, t_light *light, t_point position, t_vector eyev)
{
	t_vector	normalv;
	t_vector	lightv;
	float		light_dot_normal;
	t_vector	reflectv;
	float		reflect_dot_eye;
	float		factor;
	t_color		ambient;
	t_color		effective_color;
	t_color		diffuse;
	t_color		specular;

	if (!obj || !light)
		return ((t_color){1, 1, 1});
	normalv = normal_at(obj, position);
	effective_color = color_mix(obj->material.color, light->intensity);
	lightv = vector_normalize(tuple_subtract(light->position, position));
	ambient = color_multiply(effective_color, obj->material.ambient);
	light_dot_normal = dot(lightv, normalv);
	if (light_dot_normal < 0)
	{
		diffuse = (t_color){0, 0, 0};
		specular = (t_color){0, 0, 0};
	}
	else
	{
		diffuse = color_multiply(
				color_multiply(effective_color, obj->material.diffuse),
				light_dot_normal);
		reflectv = reflect(tuple_negate(lightv), normalv);
		reflect_dot_eye = dot(reflectv, eyev);
		if (reflect_dot_eye <= 0)
			specular = (t_color){0, 0, 0};
		else
		{
			factor = powf(reflect_dot_eye, obj->material.shininess);
			specular = color_multiply(
				color_multiply(light->intensity, obj->material.specular),
				factor);
		}
	}
	return (color_sum(color_sum(ambient, diffuse), specular));
}
