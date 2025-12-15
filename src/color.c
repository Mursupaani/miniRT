/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 10:18:46 by anpollan          #+#    #+#             */
/*   Updated: 2025/12/05 18:06:20 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

t_color	color_mix(t_color color_obj, t_color color_light)
{
	return ((t_color){color_obj.r * color_light.r,
				color_obj.g * color_light.g,
				color_obj.b * color_light.b});
}

t_color	color_multiply(t_color color, double multiplier)
{
	return ((t_color){color.r * multiplier,
			color.g * multiplier,
			color.b * multiplier});
}

t_color	color_sum(t_color color1, t_color color2)
{
	return ((t_color){color1.r + color2.r,
				color1.g + color2.g,
				color1.b + color2.b});
}
