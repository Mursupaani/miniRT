/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 18:37:01 by anpollan          #+#    #+#             */
/*   Updated: 2025/12/01 18:51:56 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector	reflect(t_vector in, t_vector normal)
{
	float	scale;

	scale = 2 * vector_dot_product(in, normal);
	return (tuple_subtract(in, tuple_scale_multiply(normal, scale)));
}
