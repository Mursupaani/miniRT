/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects_utils2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaaskel <jjaaskel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 15:46:47 by anpollan          #+#    #+#             */
/*   Updated: 2026/02/06 12:51:20 by jjaaskel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	get_cylinder_data(char **line, t_specs *s, t_app *app)
{
	skip_whitespace(line);
	if (!parse_point(line, &s->position))
		parse_error("Invalid cylinder position", app);
	skip_whitespace(line);
	if (!parse_vector(line, &s->axis) || !is_valid_axis(s->axis))
		parse_error("Invalid cylinder axis", app);
	skip_whitespace(line);
	if (!parse_double(line, &s->diameter) || s->diameter <= 0)
		parse_error("Invalid cylinder diameter", app);
	skip_whitespace(line);
	if (!parse_double(line, &s->height) || s->height <= 0)
		parse_error("Invalid cylinder height", app);
	skip_whitespace(line);
	if (!parse_color(line, &s->color))
		parse_error("Invalid cylinder color", app);
}

bool	is_valid_axis(t_vector v)
{
	return (v.x >= -1.0 && v.x <= 1.0 && v.y >= -1.0 && v.y <= 1.0
		&& v.z >= -1.0 && v.z <= 1.0);
}

void	validate_normal_vector(t_vector normal, t_app *app)
{
	if (normal.x < -1.0 || normal.x > 1.0
		|| normal.y < -1.0 || normal.y > 1.0
		|| normal.z < -1.0 || normal.z > 1.0)
		parse_error("Plane normal must be normalized [-1,1]", app);
}

void	validate_orientation_vector(t_vector ornt, t_app *app)
{
	if (ornt.x < -1.0 || ornt.x > 1.0
		|| ornt.y < -1.0 || ornt.y > 1.0
		|| ornt.z < -1.0 || ornt.z > 1.0)
		parse_error("Camera ornt must be normalized [-1,1]", app);
	if (doubles_are_equal(0, ornt.x) && doubles_are_equal(0, ornt.y)
		&& doubles_are_equal(0, ornt.z))
		parse_error("Cannot divide by zero", app);
}
