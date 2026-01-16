/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_math.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 17:17:04 by anpollan          #+#    #+#             */
/*   Updated: 2026/01/16 18:35:37 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	blend_colors_at_point(t_point p, t_color a, t_color b)
{
	return (
		color_sum(a, color_multiply(color_subtract(b, a), (p.x - floor(p.x)))));
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

t_color	color_subtract(t_color color1, t_color color2)
{
	return ((t_color){color1.r - color2.r,
		color1.g - color2.g,
		color1.b - color2.b});
}
