/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 15:38:24 by anpollan          #+#    #+#             */
/*   Updated: 2025/12/16 15:58:33 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_pattern	no_pattern(void)
{
	t_pattern	empty;

	empty.type = NONE;
	empty.a = (t_color){DBL_MIN, DBL_MIN, DBL_MIN};
	empty.b = (t_color){DBL_MIN, DBL_MIN, DBL_MIN};
	empty.transform = matrix4_identity();
	empty.inverse_transform = empty.transform;
	empty.inverse_transpose = empty.transform;
	return (empty);
}

t_material	material_change_color(t_material material, t_color color)
{
	t_material	ret;

	ret.color = color;
	ret.ambient = material.ambient;
	ret.diffuse = material.diffuse;
	ret.specular = material.specular;
	ret.shininess = material.shininess;
	return (ret);
}

t_material	material_with_color(t_color color)
{
	t_material	material;

	material.color = color;
	material.ambient = AMBIENT;
	material.diffuse = DIFFUSE;
	material.specular = SPECULAR;
	material.shininess = SHININESS;
	return (material);
}

t_material	material(void)
{
	t_material	material;

	material.ambient = AMBIENT;
	material.diffuse = DIFFUSE;
	material.specular = SPECULAR;
	material.shininess = SHININESS;
	material.reflective = 0;
	material.color = (t_color){1, 1, 1};
	material.pattern = no_pattern();
	return (material);
}
