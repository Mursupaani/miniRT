/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 10:13:15 by anpollan          #+#    #+#             */
/*   Updated: 2025/12/05 19:14:11 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

t_light	*point_light(t_point position, t_color intensity)
{
	t_light	*point_light;

	point_light = ft_calloc(1, sizeof(t_light));
	if (!point_light)
		return (NULL);
	point_light->intensity = intensity;
	point_light->position = position;
	return (point_light);
}
