/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light_and_camera.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaaskel <jjaaskel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 17:33:57 by anpollan          #+#    #+#             */
/*   Updated: 2026/01/07 14:13:18 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	parse_ambient(char *line, t_app *app)
{
	double	ratio;
	t_color	color;

	line++;
	skip_whitespace(&line);
	if (!parse_double(&line, &ratio) || ratio < 0.0 || ratio > 1.0)
		parse_error("Invalid ambient lighting ratio", app);
	skip_whitespace(&line);
	if (!parse_color(&line, &color))
		parse_error("Invalid ambient lighting color", app);
	if (app->scene->ambient_ratio > 0.0)
		parse_error("Multiple ambient lighting definitions", app);
	app->scene->ambient_ratio = ratio;
	app->scene->ambient_color = color;
}

void	parse_camera(char *line, t_app *app)
{
	t_point		pos;
	t_vector	ornt;
	double		fov;

	line++;
	skip_whitespace(&line);
	if (!parse_point(&line, &pos))
		parse_error("Invalid camera pos", app);
	skip_whitespace(&line);
	if (!parse_vector(&line, &ornt))
		parse_error("Invalid camera ornt", app);
	if (ornt.x < -1.0 || ornt.x > 1.0 || ornt.y < -1.0 || ornt.y > 1.0
		|| ornt.z < -1.0 || ornt.z > 1.0)
		parse_error("Camera ornt must be normalized [-1,1]", app);
	skip_whitespace(&line);
	if (!parse_double(&line, &fov) || fov < 0 || fov > 180)
		parse_error("Invalid camera FOV (must be 0-180)", app);
	if (app->scene->camera)
		parse_error("Multiple cameras defined", app);
	app->scene->camera = camera(app->monitor_width, app->monitor_height, fov * M_PI / 180.0);
	if (!app->scene->camera)
		exit_and_free_memory(ERROR_PARSING, app);
	app->scene->camera->transform = view_transform(pos, point(pos.x + ornt.x,
		pos.y + ornt.y, pos.z + ornt.z), vector(0, 1, 0), app->scene->camera);
}

void	parse_light(char *line, t_app *app)
{
	t_point		pos;
	double		brightness;
	t_color		color;

	line++;
	skip_whitespace(&line);
	if (!parse_point(&line, &pos))
		parse_error("Invalid light pos", app);
	skip_whitespace(&line);
	if (!parse_double(&line, &brightness) || brightness < 0.0 || brightness > 1.0)
		parse_error("Invalid light brightness ratio", app);
	skip_whitespace(&line);
	if (!parse_color(&line, &color))
		parse_error("Invalid light color", app);
	if (app->scene->light)
		parse_error("Multiple lights defined", app);
	color = color_multiply(color, brightness);
	app->scene->light = point_light(pos, color);
	if (!app->scene->light)
		exit_and_free_memory(ERROR_PARSING, app);
}






