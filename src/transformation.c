/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 10:51:29 by anpollan          #+#    #+#             */
/*   Updated: 2025/11/24 18:07:32 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_matrix4	translation_matrix4(
	double scale_x, double scale_y, double scale_z)
{
	t_matrix4	translation;
	int			i;
	int			j;

	ft_bzero(&translation, sizeof(translation));
	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			if (i == j)
				translation.data[i][j] = 1;
			else if (j == 3)
			{
				if (i == 0)
					translation.data[i][j] = scale_x;
				else if (i == 1)
					translation.data[i][j] = scale_y;
				else if (i == 2)
					translation.data[i][j] = scale_z;
			}
		}
	}
	return (translation);
}

t_matrix4	scaling_matrix4(double scale_x, double scale_y, double scale_z)
{
	t_matrix4	scalar;

	ft_bzero(&scalar, sizeof(scalar));
	scalar.data[0][0] = scale_x;
	scalar.data[1][1] = scale_y;
	scalar.data[2][2] = scale_z;
	scalar.data[3][3] = 1;
	return (scalar);
}

t_matrix4	shearing(t_shear shear)
{
	t_matrix4	shearing;

	ft_bzero(&shearing, sizeof(shearing));
	shearing.data[0][0] = 1;
	shearing.data[0][1] = shear.xy;
	shearing.data[0][2] = shear.xz;
	shearing.data[1][0] = shear.yx;
	shearing.data[1][1] = 1;
	shearing.data[1][2] = shear.yz;
	shearing.data[2][0] = shear.zx;
	shearing.data[2][1] = shear.zy;
	shearing.data[2][2] = 1;
	shearing.data[3][3] = 1;
	return (shearing);
}
