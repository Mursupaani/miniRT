/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_selected_object.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 13:20:12 by anpollan          #+#    #+#             */
/*   Updated: 2026/01/15 15:48:32 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_matrix4	store_pos_and_set_pos_to_origin(t_object *obj)
{
	t_matrix4	orig_pos;

	orig_pos.data[0][3] = obj->transform.data[0][3];
	orig_pos.data[1][3] = obj->transform.data[1][3];
	orig_pos.data[2][3] = obj->transform.data[2][3];
	obj->transform.data[0][3] = 0;
	obj->transform.data[1][3] = 0;
	obj->transform.data[2][3] = 0;
	return (orig_pos);
}

static void	set_obj_back_to_original_pos(t_object *obj, t_matrix4 orig_pos)
{
	obj->transform.data[0][3] = orig_pos.data[0][3];
	obj->transform.data[1][3] = orig_pos.data[1][3];
	obj->transform.data[2][3] = orig_pos.data[2][3];
	set_transform(obj, obj->transform);
}

void	resize_selected_object(t_app *app, double ydelta)
{
	double	scale_factor;
	t_matrix4	orig_pos;

	orig_pos = store_pos_and_set_pos_to_origin(app->selected_object);
	scale_factor = 1 + (0.01 * ydelta);
	if (mlx_is_key_down(app->mlx, MLX_KEY_X))
		add_transform(app->selected_object, scaling_matrix4(scale_factor, 1, 1));
	else if (mlx_is_key_down(app->mlx, MLX_KEY_Z))
		add_transform(app->selected_object, scaling_matrix4(1, 1, scale_factor));
	else if (mlx_is_key_down(app->mlx, MLX_KEY_Y))
		add_transform(app->selected_object, scaling_matrix4(1, scale_factor, 1));
	else
		add_transform(app->selected_object, scaling_matrix4(scale_factor, scale_factor, scale_factor));
	set_obj_back_to_original_pos(app->selected_object, orig_pos);
	app->data_changed = true;
}

void	rotate_selected_object(t_app *app, double ydelta)
{
	t_matrix4	orig_pos;

	orig_pos = store_pos_and_set_pos_to_origin(app->selected_object);
	if (mlx_is_key_down(app->mlx, MLX_KEY_X))
		add_transform(app->selected_object, rotation_x(ydelta * (M_PI / 180)));
	else if (mlx_is_key_down(app->mlx, MLX_KEY_Y))
		add_transform(app->selected_object, rotation_y(ydelta * (M_PI / 180)));
	else if (mlx_is_key_down(app->mlx, MLX_KEY_Z))
		add_transform(app->selected_object, rotation_z(ydelta * (M_PI / 180)));
	else
	{
		set_obj_back_to_original_pos(app->selected_object, orig_pos);
		return ;
	}
	set_obj_back_to_original_pos(app->selected_object, orig_pos);
	app->data_changed = true;
}
