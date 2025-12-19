/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 16:32:27 by anpollan          #+#    #+#             */
/*   Updated: 2025/12/19 17:27:54 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	max_of_min_t(double xtmin, double ytmin, double ztmin)
{
	double	max;

	max = -INFINITY;
	if (xtmin > max)
		max = xtmin;
	if (ytmin > max)
		max = ytmin;
	if (ztmin > max)
		max = ztmin;
	return (max);
}

double	min_of_max_t(double xtmax, double ytmax, double ztmax)
{
	double	min;

	min = INFINITY;
	if (xtmax < min)
		min = xtmax;
	if (ytmax < min)
		min = ytmax;
	if (ztmax < min)
		min = ztmax;
	return (min);
}

void	swap_doubles(double *tmin, double *tmax)
{
	double	temp;

	temp = *tmin;
	*tmin = *tmax;
	*tmax = temp;
}
