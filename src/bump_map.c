/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 15:11:12 by anpollan          #+#    #+#             */
/*   Updated: 2026/01/01 18:17:25 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	get_sphere_tangent_and_bitangent(t_vector local_normal, t_bump_map *bm)
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

void	get_plane_tangent_and_bitangent(t_bump_map *bm)
{
	bm->tangent = vector(1, 0, 0);
	bm->bitangent = vector(0, 0, 1);
}

t_color	sample_hit(mlx_texture_t *bump_map, uint x, uint y)
{
	int			offset;
	t_color255	sample;

	if (x >= bump_map->width) x = bump_map->width - 1;
	if (y >= bump_map->height) y = bump_map->height - 1;
	offset = calculate_pixel_offset(x, y, bump_map);
	sample.r = (uint32_t)bump_map->pixels[offset];
	sample.g = (uint32_t)bump_map->pixels[offset + 1];
	sample.b = (uint32_t)bump_map->pixels[offset + 2];
	return (color_from_color255(sample));
}

void	calculate_steps(t_bump_map *bm)
{
	bm->step_u = 1.0 / bm->bump_map->width;
	bm->step_v = 1.0 / bm->bump_map->height;
}

void	calculate_slopes(t_bump_map *bm)
{
	bm->slope_u = (bm->sample_hit.r - bm->sample_step_u.r) / bm->step_u;
	bm->slope_v = (bm->sample_hit.r - bm->sample_step_v.r) / bm->step_v;
}

void	sample_bump_map(t_bump_map *bm, t_uv_map uv)
{
	uint		x;
	uint		y;
	uint		x_offset;
	uint		y_offset;

	x = (uint)(uv.u * (bm->bump_map->width - 1));
	y = (uint)((1 - uv.v) * (bm->bump_map->height - 1));
	x_offset = (x + 1) % bm->bump_map->width;
	y_offset = (y + 1) % bm->bump_map->width;
	bm->sample_hit = sample_hit(bm->bump_map, x, y);
	bm->sample_step_u = sample_hit(bm->bump_map, x_offset, uv.v);
	bm->sample_step_v = sample_hit(bm->bump_map, y_offset, uv.v);
}

void	get_tangent_and_bitangent(t_object_type obj_type, t_vector local_normal, t_bump_map *bm)
{
	// fix cylinder
	if (obj_type == SPHERE || obj_type == CYLINDER)
		get_sphere_tangent_and_bitangent(local_normal, bm);
	else if (obj_type == PLANE || obj_type == CUBE)
		get_plane_tangent_and_bitangent(bm);
}

void	apply_bump_map_on_normal(t_object *obj, t_vector *local_normal, t_point local_point)
{
	t_bump_map	bm;
	t_uv_map	uv;
	t_vector	bump_u;
	t_vector	bump_v;

	bm = obj->bump_map;
	uv = bm.uv_map(local_point);
	calculate_steps(&bm);
	sample_bump_map(&bm, uv);
	calculate_slopes(&bm);
	get_tangent_and_bitangent(obj->type, *local_normal, &bm);
	bump_u = tuple_scale_multiply(bm.tangent, bm.slope_u * BUMP_MAP_SCALE);
	bump_v = tuple_scale_multiply(bm.bitangent, bm.slope_v * BUMP_MAP_SCALE);
	*local_normal = normalize(
		tuple_subtract(tuple_subtract(*local_normal, bump_u), bump_v));
}
