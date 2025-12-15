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

t_tuple	tuple(double x, double y, double z, double w)
{
	t_tuple	tuple;

	ft_bzero(&tuple, sizeof(t_tuple));
	tuple.x = x;
	tuple.y = y;
	tuple.z = z;
	tuple.w = w;
	return (tuple);
}

t_vector	vector(double x, double y, double z)
{
	return (tuple(x, y, z, 0));
}

t_point	point(double x, double y, double z)
{
	return (tuple(x, y, z, 1));
}
