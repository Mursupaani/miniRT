/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 15:15:33 by anpollan          #+#    #+#             */
/*   Updated: 2025/12/10 18:43:16 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	vector_magnitude(t_vector vector)
{
	return (sqrt(vector.x * vector.x
			+ vector.y * vector.y
			+ vector.z * vector.z
			+ vector.w * vector.w));
}

t_vector	normalize(t_vector v)
{
	double	magnitude;

	if (v.w != 0)
	{
		printf("Can't normalize a point\n");
		return (vector(0.0f, 0.0f, 0.0f));
	}
	magnitude = vector_magnitude(v);
	return (vector(v.x / magnitude,
			v.y / magnitude,
			v.z / magnitude));
}

double	dot(t_vector a, t_vector b)
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

t_vector	cross(t_vector a, t_vector b)
{
	if (a.w != 0 || b.w != 0)
	{
		printf("Can't execute cross product if both args are not vectors\n");
		return (vector(0, 0, 0));
	}
	return (vector(a.y * b.z - a.z * b.y,
			a.z * b.x - a.x * b.z,
			a.x * b.y - a.y * b.x));
}
