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
	return (doubles_are_equal(a.x, b.x)
		&& doubles_are_equal(a.y, b.y)
		&& doubles_are_equal(a.z, b.z)
		&& doubles_are_equal(a.w, b.w));
}
