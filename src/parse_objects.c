/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 15:45:35 by anpollan          #+#    #+#             */
/*   Updated: 2026/01/30 15:45:36 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	parse_sphere(char *line, t_app *app)
{
	t_specs	s;

	line += 2;
	skip_whitespace(&line);
	if (!parse_point(&line, &s.center))
		parse_error("Invalid sphere position", app);
	skip_whitespace(&line);
	if (!parse_double(&line, &s.diameter) || s.diameter <= 0)
		parse_error("Invalid sphere diameter", app);
	skip_whitespace(&line);
	if (!parse_color(&line, &s.color))
		parse_error("Invalid sphere color", app);
	s.obj = create_sphere_object(s.center, s.diameter, s.color);
	if (!s.obj)
		exit_and_free_memory(ERROR_PARSING, app);
	apply_texture_to_object(s.obj, &line, app);
	apply_bump_map_to_object(s.obj, &line, app);
	apply_light_behavior(s.obj, app, line);
	app->scene->objects = add_object_to_world(s.obj, app->scene);
	if (!app->scene->objects)
		exit_and_free_memory(ERROR_PARSING, app);
}

void	parse_plane(char *line, t_app *app)
{
	t_specs	s;

	line += 2;
	skip_whitespace(&line);
	if (!parse_point(&line, &s.position))
		parse_error("Invalid plane position", app);
	skip_whitespace(&line);
	if (!parse_vector(&line, &s.normal))
		parse_error("Invalid plane normal vector", app);
	validate_normal_vector(s.normal, app);
	skip_whitespace(&line);
	if (!parse_color(&line, &s.color))
		parse_error("Invalid plane color", app);
	s.obj = create_plane_object(s.position, s.normal, s.color);
	if (!s.obj)
		exit_and_free_memory(ERROR_PARSING, app);
	apply_texture_to_object(s.obj, &line, app);
	apply_bump_map_to_object(s.obj, &line, app);
	app->scene->objects = add_object_to_world(s.obj, app->scene);
	if (!app->scene->objects)
		exit_and_free_memory(ERROR_PARSING, app);
}

void	parse_cylinder(char *line, t_app *app)
{
	t_specs		s;
	t_object	*cyl;

	line += 2;
	get_cylinder_data(&line, &s, app);
	cyl = create_cylinder_object(s);
	if (!cyl)
		exit_and_free_memory(ERROR_PARSING, app);
	apply_texture_to_object(cyl, &line, app);
	apply_bump_map_to_object(cyl, &line, app);
	app->scene->objects = add_object_to_world(cyl, app->scene);
	if (!app->scene->objects)
		exit_and_free_memory(ERROR_PARSING, app);
}

void	parse_cube(char *line, t_app *app)
{
	t_specs		s;
	t_object	*cube;

	line += 2;
	get_cylinder_data(&line, &s, app);
	cube = create_cube_object(s);
	if (!cube)
		exit_and_free_memory(ERROR_PARSING, app);
	apply_texture_to_object(cube, &line, app);
	apply_bump_map_to_object(cube, &line, app);
	app->scene->objects = add_object_to_world(cube, app->scene);
	if (!app->scene->objects)
		exit_and_free_memory(ERROR_PARSING, app);
}

void	parse_cone(char *line, t_app *app)
{
	t_specs		s;
	t_object	*cone;

	line += 2;
	get_cylinder_data(&line, &s, app);
	cone = create_cone_object(s);
	if (!cone)
		exit_and_free_memory(ERROR_PARSING, app);
	apply_texture_to_object(cone, &line, app);
	apply_bump_map_to_object(cone, &line, app);
	app->scene->objects = add_object_to_world(cone, app->scene);
	if (!app->scene->objects)
		exit_and_free_memory(ERROR_PARSING, app);
}
