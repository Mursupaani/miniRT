/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 16:04:18 by anpollan          #+#    #+#             */
/*   Updated: 2025/11/18 16:04:30 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	matrices_are_equal(float m1[4][4], float m2[4][4], int w, int h)
{
	int	i;
	int	j;

	if (!m1 || !m2)
		return (false);
	i = 0;
	while (i < h)
	{
		j = 0;
		while (j < w)
		{
			if (!floats_are_equal(m1[i][j], m2[i][j]))
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}
