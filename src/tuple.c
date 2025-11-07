/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 11:43:26 by anpollan          #+#    #+#             */
/*   Updated: 2025/11/07 17:34:40 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_tuple	*new_tuple(float x, float y, float z, float w)
{
	t_tuple	*tuple;

	tuple = (t_tuple *)malloc(sizeof(t_tuple));
	if (!tuple)
		return (NULL);
	tuple->x = x;
	tuple->y = y;
	tuple->z = z;
	tuple->w = w;
	return (tuple);
}

t_vector	*new_vector(float x, float y, float z)
{
	return (new_tuple(x, y, z, 0));
}

t_point	*new_point(float x, float y, float z)
{
	return (new_tuple(x, y, z, 1));
}
