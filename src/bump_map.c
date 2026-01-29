/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 15:11:12 by anpollan          #+#    #+#             */
/*   Updated: 2026/01/16 18:24:08 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	sample_hit(mlx_texture_t *bump_map, uint32_t x, uint32_t y)
{
	int			offset;
	t_color255	sample;

	if (x >= bump_map->width)
		x = bump_map->width - 1;
	if (y >= bump_map->height)
		y = bump_map->height - 1;
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
	uint32_t		x;
	uint32_t		y;
	uint32_t		x_offset;
	uint32_t		y_offset;

	x = (uint32_t)(uv.u * (bm->bump_map->width)) % bm->bump_map->width;
	y = (uint32_t)((1 - uv.v) * (bm->bump_map->height)) % bm->bump_map->height;
	x_offset = (x + 1) % bm->bump_map->width;
	y_offset = (y + 1) % bm->bump_map->height;
	bm->sample_hit = sample_hit(bm->bump_map, x, y);
	bm->sample_step_u = sample_hit(bm->bump_map, x_offset, y);
	bm->sample_step_v = sample_hit(bm->bump_map, x, y_offset);
}

void	apply_bump_map_on_normal(
	t_object *obj, t_vector *local_normal, t_point local_point)
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
