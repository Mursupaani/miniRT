/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 10:13:15 by anpollan          #+#    #+#             */
/*   Updated: 2025/12/05 11:20:06 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_point_light	*point_light(t_point position, float intensity)
{
	t_point_light	*point_light;

	point_light = ft_calloc(1, sizeof(t_point_light));
	if (!point_light)
		return (NULL);
	point_light->intensity = intensity;
}
