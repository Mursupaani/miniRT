/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv_image.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 12:47:12 by anpollan          #+#    #+#             */
/*   Updated: 2025/12/28 15:56:00 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_uv_ptrn	uv_image(mlx_texture_t	*image)
{
	t_uv_ptrn	uv_pattern;;

	uv_pattern.type = UV_TEXTURE;
	uv_pattern.texture = image;
	uv_pattern.width = image->width;
	uv_pattern.height = image->height;
	uv_pattern.a = color(DBL_MIN, DBL_MIN, DBL_MIN);
	uv_pattern.b = color(DBL_MIN, DBL_MIN, DBL_MIN);
	return (uv_pattern);
}

t_color	pixel_at(mlx_texture_t *texture, int x, int y)
{
	int			offset;
	uint32_t	hex_color;

	offset = y * texture->bytes_per_pixel * texture->width + x * texture->bytes_per_pixel;
	hex_color = (uint32_t)(texture->pixels[offset]);
	return (color_from_hex_color(hex_color));
}
