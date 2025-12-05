/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 10:18:46 by anpollan          #+#    #+#             */
/*   Updated: 2025/12/05 10:44:14 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color_1	color(float r, float g, float b)
{
	t_color_1	color;

	color.r = r;
	color.g = g;
	color.b = b;
	return (color);
}

t_color_255	color_255(
		unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
	t_color_255	color;

	color.r = r;
	color.g = g;
	color.b = b;
	color.a = a;
	color.rgba = (r << 24) + (g << 16) + (b << 8) + a;
	return (color);
}

t_color_1	color_1_from_color255(t_color_255 color_255)
{
	t_color_1	color_1;

	color_1.r = color_255.r / 255.0f;
	color_1.g = color_255.g / 255.0f;
	color_1.b = color_255.b / 255.0f;
	color_1.a = color_255.a / 255.0f;
	return (color_1);
}
