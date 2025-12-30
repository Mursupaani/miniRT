#include "minirt.h"

static void	free_textures(mlx_texture_t *textures[6])
{
	int	i;

	i = -1;
	while (textures[++i])
	{
		mlx_delete_texture(textures[i]);
		textures[i] = NULL;
	}
}

void	free_object_array(t_object **objs)
{
	int	i;

	if (!objs)
		return ;
	i = -1;
	while (objs[++i])
	{
		if (objs[i]->material.pattern.type == MAP)
			free_textures(objs[i]->material.pattern.uv_pattern.textures);
		free(objs[i]);
		objs[i] = NULL;
	}
	free(objs);
	objs = NULL;
}

void	add_transform(t_object *object, t_matrix4 transform)
{
	if (!object)
		return ;
	object->transform = matrix4_multiply(transform, object->transform);
	object->inverse_transform = matrix4_invert(object->transform);
	object->inverse_transpose = matrix4_transpose(object->inverse_transform);
}

void	set_transform(t_object *object, t_matrix4 transform)
{
	if (!object)
		return ;
	object->transform = transform;
	object->inverse_transform = matrix4_invert(transform);
	object->inverse_transpose = matrix4_transpose(object->inverse_transform);
}

t_object	*object_new(t_object_type type)
{
	t_object	*obj;

	obj = ft_calloc(1, sizeof(t_object));
	if (!obj)
		return (NULL);
	obj->type = type;
	obj->center = point(0, 0, 0);
	obj->diameter = 1;
	obj->height = 1;
	obj->material = material();
	obj->transform = matrix4_identity();
	obj->inverse_transform = obj->transform;
	obj->inverse_transpose = obj->transform;
	if (type == CYLINDER || type == CONE)
	{
		obj->minimum = -INFINITY;
		obj->maximum = INFINITY;
		obj->closed = false;
	}
	else
	{
		obj->minimum = 0;
		obj->maximum = 0;
		obj->closed = true;
	}
	return (obj);
}
