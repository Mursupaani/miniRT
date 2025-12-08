/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 15:38:24 by anpollan          #+#    #+#             */
/*   Updated: 2025/12/05 18:43:14 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
	material.color = (t_color){1, 1, 1};
	return (material);
}
