/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhana <juhana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 18:37:01 by anpollan          #+#    #+#             */
/*   Updated: 2026/01/16 20:50:30 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector	reflect(t_vector in, t_vector normal)
{
	double	scale;

	scale = 2 * dot(in, normal);
	return (tuple_subtract(in, tuple_scale_multiply(normal, scale)));
}
