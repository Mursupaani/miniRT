/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 10:18:46 by anpollan          #+#    #+#             */
/*   Updated: 2025/12/16 17:17:50 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

u_int32_t	color_hex_from_color255(t_color255 color255)
{
	return ((color255.r << 24) + (color255.g << 16) + (color255.b << 8) + 255);
}

u_int32_t	color_hex_from_color(t_color color)
{
	if (color.r > 1)
		color.r = 1;
	if (color.g > 1)
		color.g = 1;
	if (color.b > 1)
		color.b = 1;
	if (color.r < 0)
		color.r = 0;
	if (color.g < 0)
		color.g = 0;
	if (color.b < 0)
		color.b = 0;
	return (((int)(color.r * 255) << 24)
	+ ((int)(color.g * 255) << 16)
	+ ((int)(color.b * 255) << 8)
	+ 255);
}

t_color	color_from_color255(t_color255 color_255)
{
	t_color	color;

	color.r = color_255.r / 255.0f;
	color.g = color_255.g / 255.0f;
	color.b = color_255.b / 255.0f;
	return (color);
}

t_color	color(double r, double g, double b)
{
	t_color	color;

	color.r = r;
	color.g = g;
	color.b = b;
	return (color);
}

t_color255	color255(
		unsigned char r, unsigned char g, unsigned char b)
{
	t_color255	color255;

	color255.r = r;
	color255.g = g;
	color255.b = b;
	return (color255);
}
