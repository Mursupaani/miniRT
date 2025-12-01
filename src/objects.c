#include "minirt.h"


void	set_transform(t_object *object, t_matrix4 transform)
{
	if (!object)
		return ;
	object->transform = transform;
	object->inverse_transform = matrix4_invert(transform);
}

t_object	*sphere_new(t_point center, float diameter, t_color_255 color)
{
	t_object	*sphere;

	sphere = ft_calloc(1, sizeof(t_object));
	if (!sphere)
		return (NULL);
	sphere->type = SPHERE;
	sphere->center = center;
	sphere->diameter = diameter;
	sphere->height = diameter;
	sphere->color_255 = color;
	sphere->color_1 = color_1_from_color255(color);
	if (tuples_are_equal(init_point(0, 0, 0), center))
	{
		sphere->transform = matrix4_identity();
		sphere->inverse_transform = sphere->transform;
	}
	else
		set_transform(sphere, init_translation_matrix4(center.x, center.y, center.z));
	return (sphere);
}
//
// t_object	*sphere_new(void)
// {
// 	t_object	*sphere;
//
// 	sphere = malloc(sizeof(t_object));
// 	if (!sphere)
// 		return (NULL);
// 	sphere->type = SPHERE;
// 	sphere->transform = matrix4_identity();
// 	sphere->inverse_transform = matrix4_identity();
// 	sphere->center = init_point(0, 0, 0);
// 	return (sphere);
// }
