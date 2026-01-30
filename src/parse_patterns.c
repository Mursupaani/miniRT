/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_patterns.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 20:09:54 by anpollan          #+#    #+#             */
/*   Updated: 2026/01/30 20:34:18 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	parse_test_pattern(t_object *obj, char **line)
{
	(*line) += 4;
	skip_whitespace(line);
	obj->material.pattern = test_pattern();
}

static void	parse_ring_pattern(t_object *obj, char **line, t_app *app)
{
	t_color	color;

	(*line) += 4;
	skip_whitespace(line);
	if (!parse_color(line, &color))
		parse_error("Invalid ring color", app);
	obj->material.pattern = ring_pattern(obj->material.color, color);
	set_pattern_transform(
		&obj->material.pattern, scaling_matrix4(0.25, 0.25, 0.25));
}

static void	parse_stripe_pattern(t_object *obj, char **line, t_app *app)
{
	t_color	color;

	(*line) += 6;
	skip_whitespace(line);
	if (!parse_color(line, &color))
		parse_error("Invalid stripe color", app);
	obj->material.pattern = stripe_pattern(obj->material.color, color);
	set_pattern_transform(
		&obj->material.pattern, scaling_matrix4(0.25, 0.25, 0.25));
}

static void	parse_uv_checkers(t_object *obj, char **line, t_app *app)
{
	t_pattern	uv_check;
	t_color		color;

	(*line) += 5;
	skip_whitespace(line);
	if (!parse_color(line, &color))
		parse_error("Invalid checkers color", app);
	uv_check = uv_checkers(16, 8, obj->material.color, color);
	if (obj->type == SPHERE)
		obj->material.pattern = texture_map(uv_check, spherical_map);
	else if (obj->type == PLANE)
		obj->material.pattern = texture_map(uv_check, planar_map);
	else if (obj->type == CUBE)
		obj->material.pattern = texture_map(uv_check, cubic_map);
	else if (obj->type == CYLINDER || obj->type == CONE)
		obj->material.pattern = texture_map(uv_check, cylindrical_map);
}

void	parse_pattern(t_object *obj, char **line, t_app *app)
{
	skip_whitespace(line);
	if (ft_strncmp(*line, "pattern:", 8) == 0)
	{
		skip_whitespace(line);
		(*line) += 8;
		if (ft_strncmp(*line, "stripe", 6) == 0)
			parse_stripe_pattern(obj, line, app);
		else if (ft_strncmp(*line, "ring", 4) == 0)
			parse_ring_pattern(obj, line, app);
		else if (ft_strncmp(*line, "test", 4) == 0)
			parse_test_pattern(obj, line);
		else if (ft_strncmp(*line, "check", 5) == 0)
			parse_uv_checkers(obj, line, app);
		else
			parse_error("Invalid pattern type", app);
	}
}
