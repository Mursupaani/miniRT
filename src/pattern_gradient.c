/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern_gradient.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 17:13:07 by anpollan          #+#    #+#             */
/*   Updated: 2026/01/16 20:31:55 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_pattern	gradient_pattern(t_color a, t_color b)
{
	return (create_pattern(GRADIENT, a, b));
}

t_color	gradient_at(t_pattern gradient, t_point p)
{
	t_color	distance;
	double	fraction;

	distance = color_subtract(gradient.b, gradient.a);
	fraction = p.x - floor(p.x);
	return (color_sum(gradient.a, color_multiply(distance, fraction)));
}
