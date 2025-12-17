#include "minirt.h"

// static t_object *create_cylinder_object(t_point pos, double diameter, t_color color)
// {

// }
// maybe takes width?

static t_object	*create_sphere_object(t_point pos, double diameter, t_color color)
{
	t_object	*sphere;

	sphere = sphere_new();
	if (!sphere)
		return (NULL);
	sphere->material.color = color;
	set_transform(sphere, matrix4_multiply(
		translation_matrix4(pos.x, pos.y, pos.z),
		scaling_matrix4(diameter / 2.0, diameter / 2.0, diameter / 2.0)));
	return (sphere);
}

static t_object	*create_plane_object(t_point pos, t_vector normal, t_color color)
{
	t_object	*plane;

	plane = plane_new();
	if (!plane)
		return (NULL);
	plane->material.color = color;
	set_transform(plane, translation_matrix4(pos.x, pos.y, pos.z));
	(void)normal;
	return (plane);
}
