/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 14:13:42 by anpollan          #+#    #+#             */
/*   Updated: 2025/11/24 18:11:54 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	tuples_are_equal(t_tuple a, t_tuple b)
{
	return (floats_are_equal(a.x, b.x)
		&& floats_are_equal(a.y, b.y)
		&& floats_are_equal(a.z, b.z)
		&& floats_are_equal(a.w, b.w));
}
