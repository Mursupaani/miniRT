/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light_and_camera.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhana <juhana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 17:33:57 by anpollan          #+#    #+#             */
/*   Updated: 2025/12/17 15:26:42 by juhana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	parse_ambient(char *line, t_app *app)
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

static void	parse_camera(char *line, t_app *app)
{
	t_point		position;
	t_vector	orientation;
	double		fov;

	line++;
	skip_whitespace(&line);
	if (!parse_point(&line, &position))
		parse_error("Invalid camera position", app);
	skip_whitespace(&line);
	if (!parse_vector(&line, &orientation))
		parse_error("Invalid camera orientation", app);
	if (orientation.x < -1.0 || orientation.x > 1.0 ||
		orientation.y < -1.0 || orientation.y > 1.0 ||
		orientation.z < -1.0 || orientation.z > 1.0)
		parse_error("Camera orientation must be normalized [-1,1]", app);
	skip_whitespace(&line);
	if (!parse_double(&line, &fov) || fov < 0 || fov > 180)
		parse_error("Invalid camera FOV (must be 0-180)", app);
	if (app->scene->camera)
		parse_error("Multiple cameras defined", app);
	app->scene->camera = camera(app->monitor_width, app->monitor_height, fov * M_PI / 180.0);
	if (!app->scene->camera)
		exit_and_free_memory(ERROR_PARSING, app);
	app->scene->camera->transform = view_transform(
		position,
		point(position.x + orientation.x, position.y + orientation.y, position.z + orientation.z),
		vector(0, 1, 0));
}

static void	parse_light(char *line, t_app *app)
{
	t_point		position;
	double		brightness;
	t_color		color;

	line++;
	skip_whitespace(&line);
	if (!parse_point(&line, &position))
		parse_error("Invalid light position", app);
	skip_whitespace(&line);
	if (!parse_double(&line, &brightness) || brightness < 0.0 || brightness > 1.0)
		parse_error("Invalid light brightness ratio", app);
	skip_whitespace(&line);
	if (!parse_color(&line, &color))
		parse_error("Invalid light color", app);
	if (app->scene->light)
		parse_error("Multiple lights defined", app);
	color = color_multiply(color, brightness);
	app->scene->light = point_light(position, color);
	if (!app->scene->light)
		exit_and_free_memory(ERROR_PARSING, app);
}






