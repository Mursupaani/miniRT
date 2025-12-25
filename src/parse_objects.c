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
	if (normal.x < -1.0 || normal.x > 1.0 ||
		normal.y < -1.0 || normal.y > 1.0 ||
		normal.z < -1.0 || normal.z > 1.0)
		parse_error("Plane normal must be normalized [-1,1]", app);
	skip_whitespace(&line);
	if (!parse_color(&line, &color))
		parse_error("Invalid plane color", app);
	plane = create_plane_object(position, normal, color);
	if (!plane)
		exit_and_free_memory(ERROR_PARSING, app);
	app->scene->objects = add_object_to_world(plane, app->scene);
	if (!app->scene->objects)
		exit_and_free_memory(ERROR_PARSING, app);
}

static bool	is_valid_axis(t_vector v)
{
	return (v.x >= -1.0 && v.x <= 1.0 && v.y >= -1.0 && v.y <= 1.0
		&& v.z >= -1.0 && v.z <= 1.0);
}

static void	get_cylinder_data(char **line, t_specs *s, t_app *app)
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

void	parse_cylinder(char *line, t_app *app)
{
	t_specs		s;
	t_object	*cyl;

	line += 2;
	get_cylinder_data(&line, &s, app);
	cyl = create_cylinder_object(s);
	if (!cyl)
		exit_and_free_memory(ERROR_PARSING, app);
	app->scene->objects = add_object_to_world(cyl, app->scene);
	if (!app->scene->objects)
		exit_and_free_memory(ERROR_PARSING, app);
}
