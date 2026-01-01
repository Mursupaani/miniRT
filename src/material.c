/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 15:38:24 by anpollan          #+#    #+#             */
/*   Updated: 2026/01/01 15:51:52 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minirt.h"

t_pattern	test_pattern()
{
	return (create_pattern(TEST, color(1, 1, 1), color(0, 0, 0)));
	// t_pattern	test;
	//
	// test.type = TEST;
	// test.a = (t_color){1, 1, 1};
	// test.b = (t_color){0, 0, 0};
	// test.transform = matrix4_identity();
	// test.inverse_transform = test.transform;
	// test.inverse_transpose = test.transform;
	// return (test);
}

static t_pattern	no_pattern(void)
{
	t_pattern	empty;

	ft_bzero(&empty, sizeof(t_pattern));
	empty.type = NONE;
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
	material.transparency = 0;
	material.refractive_index = 1;
	material.color = (t_color){1, 1, 1};
	material.pattern = no_pattern();
	return (material);
}
