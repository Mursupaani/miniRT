/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 16:04:18 by anpollan          #+#    #+#             */
/*   Updated: 2025/11/20 12:02:01 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	matrix4s_are_equal(t_matrix4 m1, t_matrix4 m2)
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			if (!floats_are_equal(m1.data[i][j], m2.data[i][j]))
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}
