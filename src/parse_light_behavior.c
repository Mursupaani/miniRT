/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light_behavior.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 19:35:54 by anpollan          #+#    #+#             */
/*   Updated: 2026/01/30 15:21:36 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	parse_object_diffuse(char **line, t_object *obj, t_app *app)
{
	if (!parse_double(line, &obj->material.diffuse)
		|| obj->material.diffuse < 0 || obj->material.diffuse > 1)
		parse_error("Invalid diffuse light effect value", app);
	skip_whitespace(line);
}

static void	parse_object_shininess(char **line, t_object *obj, t_app *app)
{
	if (!parse_double(line, &obj->material.shininess)
		|| obj->material.shininess < 0 || obj->material.shininess > 1)
		parse_error("Invalid shininess light effect value", app);
	skip_whitespace(line);
}

static void	parse_object_specular(char **line, t_object *obj, t_app *app)
{
	if (!parse_double(line, &obj->material.specular)
		|| obj->material.specular < 0 || obj->material.specular > 1)
		parse_error("Invalid specular light effect value", app);
	skip_whitespace(line);
}

static void	parse_object_ambient(char **line, t_object *obj, t_app *app)
{
	if (!parse_double(line, &obj->material.ambient)
		|| obj->material.ambient < 0 || obj->material.ambient > 1)
		parse_error("Invalid ambient light effect value", app);
	skip_whitespace(line);
}

void	apply_light_behavior(t_object *obj, t_app *app, char **line)
{
	skip_whitespace(line);
	if (!**line || **line == '#')
		return ;
	if (ft_strncmp(*line, "a:", 2) == 0)
	{
		(*line) += 2;
		parse_object_ambient(line, obj, app);
	}
	if (ft_strncmp(*line, "d:", 2) == 0)
	{
		(*line) += 2;
		parse_object_diffuse(line, obj, app);
	}
	if (ft_strncmp(*line, "sp:", 3) == 0)
	{
		(*line) += 3;
		parse_object_specular(line, obj, app);
	}
	if (ft_strncmp(*line, "sh:", 3) == 0)
	{
		(*line) += 3;
		parse_object_shininess(line, obj, app);
	}
	apply_reflect_and_refract(obj, app, line);
}
