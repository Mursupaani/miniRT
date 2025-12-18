/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_computations_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 14:58:10 by anpollan          #+#    #+#             */
/*   Updated: 2025/12/18 15:02:33 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	handle_n1(t_computations *comps, t_intersection **containers)
{
	int	i;

	if (containers[0] == NULL)
		comps->n1 = 1;
	else
	{
		i = 0;
		while (containers[i])
			i++;
		comps->n1 = containers[--i]->object->material.refractive_index;
	}
}

void	handle_n2(t_computations *comps, t_intersection **containers)
{
	int	i;

	if (containers[0] == NULL)
		comps->n2 = 1;
	else
	{
		i = 0;
		while (containers[i])
			i++;
		comps->n2 = containers[--i]->object->material.refractive_index;
	}
}
