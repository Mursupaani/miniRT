/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_reflection_and_refraction.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 14:55:54 by anpollan          #+#    #+#             */
/*   Updated: 2026/01/30 15:16:22 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	parse_object_refract_indx(char **line, t_object *obj, t_app *app)
{
	if (!parse_double(line, &obj->material.refractive_index)
		|| obj->material.refractive_index < 0)
		parse_error("Invalid refractive index", app);
	skip_whitespace(line);
}

static void	parse_object_refract(char **line, t_object *obj, t_app *app)
{
	if (!parse_double(line, &obj->material.transparency)
		|| obj->material.transparency < 0 || obj->material.transparency > 1)
		parse_error("Invalid transparency value", app);
	skip_whitespace(line);
}

static void	parse_object_reflect(char **line, t_object *obj, t_app *app)
{
	if (!parse_double(line, &obj->material.reflective)
		|| obj->material.reflective < 0 || obj->material.reflective > 1)
		parse_error("Invalid reflective value", app);
	skip_whitespace(line);
}

void	apply_reflect_and_refract(t_object *obj, t_app *app, char **line)
{
	skip_whitespace(line);
	if (!**line || **line == '#')
		return ;
	if (ft_strncmp(*line, "re:", 3) == 0)
	{
		(*line) += 3;
		parse_object_reflect(line, obj, app);
	}
	if (ft_strncmp(*line, "tr:", 3) == 0)
	{
		(*line) += 3;
		parse_object_refract(line, obj, app);
	}
	if (ft_strncmp(*line, "ri:", 3) == 0)
	{
		(*line) += 3;
		parse_object_refract_indx(line, obj, app);
	}
}
