/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhana <juhana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 16:04:18 by anpollan          #+#    #+#             */
/*   Updated: 2025/12/01 16:00:46 by anpollan         ###   ########.fr       */
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

t_matrix4	matrix4_identity(void)
{
	t_matrix4	matrix;
	int			i;

	ft_bzero(&matrix, sizeof(t_matrix4));
	i = 0;
	while (i < 4)
	{
		matrix.data[i][i] = 1.0f;
		i++;
	}
	return (matrix);
}
