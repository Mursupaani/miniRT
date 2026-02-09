/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light_and_camera.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhana <juhana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 17:33:57 by anpollan          #+#    #+#             */
/*   Updated: 2026/01/30 15:45:13 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	set_camera_view(t_camera *c)
{
	t_matrix4	view;

	c->forward = get_direction_from_angles(c->yaw, c->pitch);
	c->left = cross(c->world_up, c->forward);
	c->up = cross(c->forward, c->left);
	view = view_transform(c->from, tuple_sum(c->from, c->forward), c->up, c);
	set_camera_transform(c, view);
}

static void	create_or_update_light(t_point pos, t_color color, t_app *app)
{
	if (!app->scene->light)
	{
		app->scene->light = light(pos, color);
		if (!app->scene->light)
			exit_and_free_memory(ERROR_PARSING, app);
	}
	else
	{
		app->scene->light->position = pos;
		app->scene->light->intensity = color;
	}
}

void	parse_ambient_component(char **line, t_app *app)
{
	double	ratio;
	t_color	color;

	(*line)++;
	skip_whitespace(line);
	if (!parse_double(line, &ratio) || ratio < 0.0 || ratio > 1.0)
		parse_error("Invalid ambient lighting ratio", app);
	skip_whitespace(line);
	if (!parse_color(line, &color))
		parse_error("Invalid ambient lighting color", app);
	if (!app->scene->light)
	{
		app->scene->light = ft_calloc(1, sizeof(t_light));
		if (!app->scene->light)
			exit_and_free_memory(ERROR_PARSING, app);
	}
	if (app->scene->light->ambient_ratio > 0.0)
		parse_error("Multiple ambient lighting definitions", app);
	app->scene->light->ambient_ratio = ratio;
	app->scene->light->ambient_color = color;
}

void	parse_camera(char **line, t_app *app)
{
	t_point		pos;
	t_vector	ornt;
	double		fov;

	(*line)++;
	skip_whitespace(line);
	if (!parse_point(line, &pos))
		parse_error("Invalid camera pos", app);
	skip_whitespace(line);
	if (!parse_vector(line, &ornt))
		parse_error("Invalid camera ornt", app);
	validate_orientation_vector(ornt, app);
	skip_whitespace(line);
	if (!parse_double(line, &fov) || fov < 0 || fov > 180)
		parse_error("Invalid camera FOV (must be 0-180)", app);
	if (app->scene->camera)
		parse_error("Multiple cameras defined", app);
	app->scene->camera = camera(app->scrn_w, app->scrn_h, deg_to_rad(fov));
	if (!app->scene->camera)
		exit_and_free_memory(ERROR_PARSING, app);
	app->scene->camera->transform = view_transform(pos, point(pos.x + ornt.x,
				pos.y + ornt.y, pos.z + ornt.z), vector(0, 1, 0),
			app->scene->camera);
	init_camera_pitch_and_yaw(app->scene->camera);
	set_camera_view(app->scene->camera);
}

void	parse_light(char **line, t_app *app)
{
	t_point		pos;
	double		brightness;
	t_color		color;

	(*line)++;
	skip_whitespace(line);
	if (!parse_point(line, &pos))
		parse_error("Invalid light pos", app);
	skip_whitespace(line);
	if (!parse_double(line, &brightness)
		|| brightness < 0.0 || brightness > 1.0)
		parse_error("Invalid light brightness ratio", app);
	skip_whitespace(line);
	if (!parse_color(line, &color))
		parse_error("Invalid light color", app);
	if (app->scene->light && app->scene->light->intensity.r > 0.0)
		parse_error("Multiple lights defined", app);
	color = color_multiply(color, brightness);
	create_or_update_light(pos, color, app);
}
