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
	return (tuple(
			a.x + b.x,
			a.y + b.y,
			a.z + b.z,
			a.w + b.w));
}

t_tuple	tuple_subtract(t_tuple a, t_tuple b)
{
	return (tuple(
			a.x - b.x,
			a.y - b.y,
			a.z - b.z,
			a.w - b.w));
}

t_tuple	tuple_scale_multiply(t_tuple t, double scalar)
{
	return (tuple(
			t.x * scalar,
			t.y * scalar,
			t.z * scalar,
			t.w * scalar));
}

t_tuple	tuple_scale_divide(t_tuple t, double divider)
{
	return (tuple(
			t.x / divider,
			t.y / divider,
			t.z / divider,
			t.w / divider));
}

t_tuple	tuple_negate(t_tuple t)
{
	return (tuple(
			-t.x,
			-t.y,
			-t.z,
			-t.w));
}
