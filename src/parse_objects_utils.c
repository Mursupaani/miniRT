#include "minirt.h"

t_object *create_cylinder_object(t_specs s)
{
	t_object	*cyl;
	t_matrix4	rot;
	t_matrix4	trans;
	t_matrix4	scale;

	cyl = cylinder_new();
	if (!cyl)
		return (NULL);
	cyl->material.color = s.color;
	cyl->maximum = s.height / 2.0;
	cyl->minimum = -s.height / 2.0;
	cyl->closed = true;
	trans = translation_matrix4(s.position.x, s.position.y, s.position.z);
	scale = scaling_matrix4(s.diameter / 2.0, 1, s.diameter / 2.0);
	rot = rotation_matrix_from_orientation(s.axis);
	set_transform(cyl, matrix4_multiply(trans, matrix4_multiply(rot, scale)));
	return (cyl);
}


t_object	*create_sphere_object(t_point pos, double diameter, t_color color)
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

t_object	*create_plane_object(t_point pos, t_vector normal, t_color color)
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
