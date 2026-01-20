/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 17:18:27 by anpollan          #+#    #+#             */
/*   Updated: 2025/11/07 14:51:09 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	doubles_are_equal(double a, double b)
{
	return (fabs(a - b) < EPSILON);
}

double	deg_to_rad(double deg)
{
	return (deg * (M_PI / 180));
}

double	rad_to_deg(double rad)
{
	return (rad * (180 / M_PI));
}
