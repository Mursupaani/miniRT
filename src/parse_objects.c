#include "minirt.h"

void	parse_sphere(char *line, t_app *app)
{
	t_point		center;
	double		diameter;
	t_color		color;
	t_object	*sphere;

	line += 2;
	skip_whitespace(&line);
	if (!parse_point(&line, &center))
		parse_error("Invalid sphere position", app);
	skip_whitespace(&line);
	if (!parse_double(&line, &diameter) || diameter <= 0)
		parse_error("Invalid sphere diameter", app);
	skip_whitespace(&line);
	if (!parse_color(&line, &color))
		parse_error("Invalid sphere color", app);
	sphere = create_sphere_object(center, diameter, color);
	if (!sphere)
		exit_and_free_memory(ERROR_PARSING, app);
	apply_texture_to_object(sphere, &line, app);
	apply_bump_map_to_object(sphere, &line, app);
	app->scene->objects = add_object_to_world(sphere, app->scene);
	if (!app->scene->objects)
		exit_and_free_memory(ERROR_PARSING, app);
}

void	parse_plane(char *line, t_app *app)
{
	t_point		position;
	t_vector	normal;
	t_color		color;
	t_object	*plane;

	line += 2;
	skip_whitespace(&line);
	if (!parse_point(&line, &position))
		parse_error("Invalid plane position", app);
	skip_whitespace(&line);
	if (!parse_vector(&line, &normal))
		parse_error("Invalid plane normal vector", app);
	validate_normal_vector(normal, app);
	skip_whitespace(&line);
	if (!parse_color(&line, &color))
		parse_error("Invalid plane color", app);
	plane = create_plane_object(position, normal, color);
	if (!plane)
		exit_and_free_memory(ERROR_PARSING, app);
	apply_texture_to_object(plane, &line, app);
	apply_bump_map_to_object(plane, &line, app);
	app->scene->objects = add_object_to_world(plane, app->scene);
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
