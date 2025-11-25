/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_math.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhana <juhana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 11:50:47 by anpollan          #+#    #+#             */
/*   Updated: 2025/11/24 16:18:56 by juhana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_tuple	tuple_sum(t_tuple a, t_tuple b)
{
	return (init_tuple(
			a.x + b.x,
			a.y + b.y,
			a.z + b.z,
			a.w + b.w));
}

t_tuple	tuple_subtract(t_tuple a, t_tuple b)
{
	return (init_tuple(
			a.x - b.x,
			a.y - b.y,
			a.z - b.z,
			a.w - b.w));
}

t_tuple	tuple_scale_multiply(t_tuple tuple, float scalar)
{
	return (init_tuple(
			tuple.x * scalar,
			tuple.y * scalar,
			tuple.z * scalar,
			tuple.w * scalar));
}

t_tuple	tuple_scale_divide(t_tuple tuple, float divider)
{
	return (init_tuple(
			tuple.x / divider,
			tuple.y / divider,
			tuple.z / divider,
			tuple.w / divider));
}

t_tuple	tuple_negate(t_tuple tuple)
{
	return (init_tuple(
			-tuple.x,
			-tuple.y,
			-tuple.z,
			-tuple.w));
}
