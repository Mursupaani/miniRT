/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 18:20:49 by anpollan          #+#    #+#             */
/*   Updated: 2026/01/17 16:32:35 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	get_sphere_tangent_bitangent(t_vector local_normal, t_bump_map *bm)
{
	t_vector	up;
	t_vector	tangent;

	up = vector(0, 1, 0);
	tangent = cross(local_normal, up);
	if (doubles_are_equal(vector_magnitude(tangent), 0))
		bm->tangent = vector(1, 0, 0);
	else
		bm->tangent = normalize(tangent);
	bm->bitangent = normalize(cross(local_normal, bm->tangent));
}

static void	get_plane_tangent_and_bitangent(t_bump_map *bm)
{
	bm->tangent = vector(1, 0, 0);
	bm->bitangent = vector(0, 0, 1);
}

// NOTE: Cylinder caps are not yet implemented
void	get_tangent_and_bitangent(
		t_object_type obj_type, t_vector local_normal, t_bump_map *bm)
{
	if (obj_type == SPHERE || obj_type == CYLINDER)
		get_sphere_tangent_bitangent(local_normal, bm);
	else if (obj_type == PLANE || obj_type == CUBE)
		get_plane_tangent_and_bitangent(bm);
}
