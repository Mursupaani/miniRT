/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv_image.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 12:47:12 by anpollan          #+#    #+#             */
/*   Updated: 2026/01/16 20:36:40 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_pattern	uv_image_cube_same_texture(mlx_texture_t *texture)
{
	t_pattern	ptrn;

	ptrn = create_pattern(MAP, color(-1, -1, -1), color(-1, -1, -1));
	ptrn.uv_pattern.type = UV_TEXTURE;
	ptrn.uv_pattern.textures[UP] = texture;
	ptrn.uv_pattern.textures[DOWN] = texture;
	ptrn.uv_pattern.textures[LEFT] = texture;
	ptrn.uv_pattern.textures[RIGHT] = texture;
	ptrn.uv_pattern.textures[FRONT] = texture;
	ptrn.uv_pattern.textures[BACK] = texture;
	return (ptrn);
}

t_pattern	uv_image_cube(mlx_texture_t *textures[6])
{
	t_pattern	ptrn;

	ptrn = create_pattern(MAP, color(-1, -1, -1), color(-1, -1, -1));
	ptrn.uv_pattern.type = UV_TEXTURE;
	ptrn.uv_pattern.textures[UP] = textures[UP];
	ptrn.uv_pattern.textures[DOWN] = textures[DOWN];
	ptrn.uv_pattern.textures[LEFT] = textures[LEFT];
	ptrn.uv_pattern.textures[RIGHT] = textures[RIGHT];
	ptrn.uv_pattern.textures[FRONT] = textures[FRONT];
	ptrn.uv_pattern.textures[BACK] = textures[BACK];
	return (ptrn);
}

t_pattern	uv_image(mlx_texture_t *image)
{
	t_pattern	ptrn;

	ptrn = create_pattern(MAP, color(-1, -1, -1), color(-1, -1, -1));
	ptrn.uv_pattern.type = UV_TEXTURE;
	ptrn.uv_pattern.textures[UP] = image;
	ptrn.uv_pattern.width = image->width;
	ptrn.uv_pattern.height = image->height;
	return (ptrn);
}

t_color	pixel_at(mlx_texture_t *texture, int x, int y)
{
	int			offset;
	t_color255	c255;

	offset = calculate_pixel_offset(x, y, texture);
	c255.r = (uint32_t)(texture->pixels[offset]);
	c255.g = (uint32_t)(texture->pixels[offset + 1]);
	c255.b = (uint32_t)(texture->pixels[offset + 2]);
	return (color_from_color255(c255));
}
