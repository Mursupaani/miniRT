/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern_ring.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 18:16:45 by anpollan          #+#    #+#             */
/*   Updated: 2025/12/16 18:57:16 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_pattern	ring_pattern(t_color a, t_color b)
{
	t_pattern	ring;

	ring.type = RING;
	ring.a = a;
	ring.b = b;
	ring.transform = matrix4_identity();
	ring.inverse_transform = ring.transform;
	ring.inverse_transpose = ring.transform;
	return (ring);
}

t_color	ring_at(t_pattern gradient, t_point p)
{
	if ((int)(sqrt(pow(p.x, 2) + pow(p.z, 2))) % 2 == 0)
		return (gradient.a);
	else
		return (gradient.b);
}

