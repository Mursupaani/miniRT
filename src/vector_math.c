/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 15:15:33 by anpollan          #+#    #+#             */
/*   Updated: 2025/11/07 17:29:28 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	vector_magnitude(t_vector vector)
{
	return (sqrtf(vector.x * vector.x
			+ vector.y * vector.y
			+ vector.z * vector.z
			+ vector.w * vector.w));
}

t_vector	vector_normalize(t_vector vector)
{
	float	magnitude;

	if (vector.w != 0)
	{
		printf("Can't normalize a point\n");
		return (init_vector(0, 0, 0));
	}
	magnitude = vector_magnitude(vector);
	return (init_vector(vector.x / magnitude,
			vector.y / magnitude,
			vector.z / magnitude));
}

float	vector_dot_product(t_vector a, t_vector b)
{
	if (a.w != 0 || b.w != 0)
	{
		printf("Can't execute dot product if both args are not vectors\n");
		return (0);
	}
	return (a.x * b.x
		+ a.y * b.y
		+ a.z * b.z);
}

t_vector	vector_cross_product(t_vector a, t_vector b)
{
	if (a.w != 0 || b.w != 0)
	{
		printf("Can't execute cross product if both args are not vectors\n");
		return (init_vector(0, 0, 0));
	}
	return (init_vector(a.y * b.z - a.z * b.y,
			a.z * b.x - a.x * b.z,
			a.x * b.y - a.y * b.x));
}
