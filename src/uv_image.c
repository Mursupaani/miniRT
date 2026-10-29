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

int	calculate_pixel_offset(int x, int y, mlx_texture_t *texture)
{
	return (y * texture->bytes_per_pixel * texture->width
		+ x * texture->bytes_per_pixel);
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
