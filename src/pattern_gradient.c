/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern_gradient.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 17:13:07 by anpollan          #+#    #+#             */
/*   Updated: 2025/12/16 18:59:19 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_pattern	gradient_pattern(t_color a, t_color b)
{
	t_pattern	gradient;

	gradient.type = GRADIENT;
	gradient.a = a;
	gradient.b = b;
	gradient.transform = matrix4_identity();
	gradient.inverse_transform = gradient.transform;
	gradient.inverse_transpose = gradient.transform;
	return (gradient);
}

t_color	gradient_at(t_pattern gradient, t_point p)
{
	t_color	distance;
	double	fraction;

	distance = color_subtract(gradient.b, gradient.a);
	fraction = p.x - floor(p.x);
	return (color_sum(gradient.a, color_multiply(distance, fraction)));
}
