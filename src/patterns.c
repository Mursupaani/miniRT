/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   patterns.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 12:06:15 by anpollan          #+#    #+#             */
/*   Updated: 2025/12/26 19:25:10 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	pattern_at(t_pattern ptrn, t_point ptrn_point)
{
	if (ptrn.type == STRIPE)
		return (stripe_at(ptrn, ptrn_point));
	else if (ptrn.type == GRADIENT)
		return (gradient_at(ptrn, ptrn_point));
	else if (ptrn.type == RING)
		return (ring_at(ptrn, ptrn_point));
	else if (ptrn.type == CHECKERS)
		return (checkers_at(ptrn, ptrn_point));
	else if (ptrn.type == TEST)
		return ((t_color){ptrn_point.x, ptrn_point.y, ptrn_point.z});
	else if (ptrn.type == MAP)
		return (handle_uv_pattern(ptrn, ptrn_point));
	else
		return ((t_color){DBL_MIN, DBL_MIN, DBL_MIN});
}


t_color	pattern_at_shape(t_pattern ptrn, t_object *obj, t_point p)
{
	t_point	obj_point;
	t_point	ptrn_point;

	obj_point = matrix4_and_tuple_multiply(obj->inverse_transform, p);
	ptrn_point = matrix4_and_tuple_multiply(ptrn.inverse_transform, obj_point);
	return (pattern_at(ptrn, ptrn_point));
}

t_pattern	create_pattern(int type, t_color a, t_color b)
{
	t_pattern	pattern;

	pattern.a = a;
	pattern.b = b;
	pattern.transform = matrix4_identity();
	pattern.inverse_transform = pattern.transform;
	pattern.inverse_transpose = pattern.transform;
	if (type == CHECKERS)
		pattern.type = CHECKERS;
	else if (type == RING)
		pattern.type = RING;
	else if (type == STRIPE)
		pattern.type = STRIPE;
	else if (type == GRADIENT)
		pattern.type = GRADIENT;
	else if (type == TEST)
		pattern.type = TEST;
	else if (type == MAP)
		pattern.type = MAP;
	return (pattern);
}

void	set_pattern_transform(t_pattern *ptrn, t_matrix4 transform)
{
	ptrn->transform = transform;
	ptrn->inverse_transform = matrix4_invert(ptrn->transform);
	ptrn->inverse_transpose = matrix4_transpose(ptrn->inverse_transform);
}

void	add_pattern_transform(t_pattern *ptrn, t_matrix4 transform)
{
	ptrn->transform = matrix4_multiply(transform, ptrn->transform);
	ptrn->inverse_transform = matrix4_invert(ptrn->transform);
	ptrn->inverse_transpose = matrix4_transpose(ptrn->inverse_transform);
}
