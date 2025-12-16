/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   patterns.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 12:06:15 by anpollan          #+#    #+#             */
/*   Updated: 2025/12/16 16:25:36 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


t_color	pattern_at_shape(t_pattern ptrn, t_object *obj, t_point p)
{
	if (ptrn.type == STRIPE)
		return (stripe_at_object(ptrn, obj, p));
	else
		return (obj->material.color);
}

void	add_pattern_transform(t_pattern *ptrn, t_matrix4 transform)
{
	ptrn->transform = matrix4_multiply(transform, ptrn->transform);
	ptrn->inverse_transform = matrix4_invert(ptrn->transform);
	ptrn->inverse_transpose = matrix4_transpose(ptrn->inverse_transform);
}

void	set_pattern_transform(t_pattern *ptrn, t_matrix4 transform)
{
	ptrn->transform = transform;
	ptrn->inverse_transform = matrix4_invert(ptrn->transform);
	ptrn->inverse_transpose = matrix4_transpose(ptrn->inverse_transform);
}
