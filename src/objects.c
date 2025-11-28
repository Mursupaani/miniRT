#include "minirt.h"

void	set_transform(t_object *object, t_matrix4 transform)
{
	if (!object)
		return ;
	object->transform = transform;
	object->inverse_transform = matrix4_invert(transform);
}

t_object	*sphere_new(void)
{
	t_object	*sphere;

	sphere = malloc(sizeof(t_object));
	if (!sphere)
		return (NULL);
	sphere->type = SPHERE;
	sphere->transform = matrix4_identity();
	sphere->inverse_transform = matrix4_identity();
	sphere->color_1 = malloc(sizeof(t_color_1));
	if (!sphere->color_1)
		return (NULL);
	sphere->color_255 = malloc(sizeof(t_color_255));
	if (!sphere->color_255)
		return (NULL);
	sphere->center = init_point(0, 0, 0);
	return (sphere);
}
