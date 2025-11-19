/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 16:04:18 by anpollan          #+#    #+#             */
/*   Updated: 2025/11/19 14:43:07 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	matrix4s_are_equal(float (*m1)[4], float (*m2)[4])
{
	int	i;
	int	j;

	if (!m1 || !m2)
		return (false);
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			if (!floats_are_equal(m1[i][j], m2[i][j]))
				return (false);
			printf("%.0f\n", m1[i][j]);
			j++;
		}
		i++;
	}
	return (true);
}
