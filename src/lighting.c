/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 10:13:15 by anpollan          #+#    #+#             */
/*   Updated: 2025/12/10 17:44:44 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_light	*light(t_point position, t_color intensity)
{
	t_light	*point_light;

	point_light = ft_calloc(1, sizeof(t_light));
	if (!point_light)
		return (NULL);
	point_light->intensity = intensity;
	point_light->position = position;
	point_light->ambient_color = color(1, 1, 1);
	point_light->ambient_ratio = AMBIENT;
	return (point_light);
}
