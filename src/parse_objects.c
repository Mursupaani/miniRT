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
	app->scene->objects = world_add_object(app->scene, sphere);
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
	app->scene->objects = world_add_object(app->scene, plane);
	if (!app->scene->objects)
		exit_and_free_memory(ERROR_PARSING, app);
}

void	parse_cylinder(char *line, t_app *app)
{
	t_point		position;
	t_vector	axis;
	double		diameter;
	double		height;
	t_color		color;

	line += 2;
	skip_whitespace(&line);
	if (!parse_point(&line, &position))
		parse_error("Invalid cylinder position", app);
	skip_whitespace(&line);
	if (!parse_vector(&line, &axis))
		parse_error("Invalid cylinder axis", app);
	if (axis.x < -1.0 || axis.x > 1.0 ||
		axis.y < -1.0 || axis.y > 1.0 ||
		axis.z < -1.0 || axis.z > 1.0)
		parse_error("Cylinder axis must be normalized [-1,1]", app);
	skip_whitespace(&line);
	if (!parse_double(&line, &diameter) || diameter <= 0)
		parse_error("Invalid cylinder diameter", app);
	skip_whitespace(&line);
	if (!parse_double(&line, &height) || height <= 0)
		parse_error("Invalid cylinder height", app);
	skip_whitespace(&line);
	if (!parse_color(&line, &color))
		parse_error("Invalid cylinder color", app);
	// TODO: Implement cylinder object creation
	(void)position;
	(void)axis;
	(void)diameter;
	(void)height;
	(void)color;
	parse_error("Cylinder not yet implemented", app);
}
