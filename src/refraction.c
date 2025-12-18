/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refraction.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 15:31:20 by anpollan          #+#    #+#             */
/*   Updated: 2025/12/18 15:46:32 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	refracted_color(t_world *w, t_computations comps, int recursions)
{
	if (comps.object->material.transparency == 0)
		return ((t_color){0, 0, 0});
	if (recursions == 0)
		return ((t_color){0, 0, 0});
	(void)recursions;
	(void)w;
	return ((t_color){1, 1, 1});
}
