/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_inversion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 18:53:32 by anpollan          #+#    #+#             */
/*   Updated: 2025/11/20 19:07:36 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_matrix4	matrix4_invert(t_matrix4 matrix)
{
	t_matrix4	invert;
	int		i;
	int		j;
	double	determinant;

	ft_bzero(&invert, sizeof(invert));
	determinant = matrix4_determinant(matrix);
	if (determinant == 0)
		return (invert);
	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
			invert.data[j][i] = matrix4_cofactor(matrix, i, j) / determinant;
	}
	return (invert);
}
