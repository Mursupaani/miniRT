/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   patterns.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 12:06:15 by anpollan          #+#    #+#             */
/*   Updated: 2025/12/16 17:34:03 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_pattern	test_pattern()
{
	t_pattern	test;

	test.type = TEST;
	test.a = (t_color){1, 1, 1};
	test.b = (t_color){0, 0, 0};
	test.transform = matrix4_identity();
	test.inverse_transform = test.transform;
	test.inverse_transpose = test.transform;
	return (test);
}

t_color	pattern_at_shape(t_pattern ptrn, t_object *obj, t_point p)
{
	t_point	obj_point;
	t_point	ptrn_point;

	obj_point = matrix4_and_tuple_multiply(obj->inverse_transform, p);
	ptrn_point = matrix4_and_tuple_multiply(ptrn.inverse_transform, obj_point);
	if (ptrn.type == STRIPE)
		return (stripe_at(ptrn, ptrn_point));
	else if (ptrn.type == GRADIENT)
		return (gradient_at(ptrn, ptrn_point));
	else if (ptrn.type == TEST)
		return ((t_color){ptrn_point.x, ptrn_point.y, ptrn_point.z});
	else
		return ((t_color){DBL_MIN, DBL_MIN, DBL_MIN});
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
