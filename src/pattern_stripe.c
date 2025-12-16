/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern_stripe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 15:55:11 by anpollan          #+#    #+#             */
/*   Updated: 2025/12/16 16:06:01 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_pattern	stripe_pattern(t_color a, t_color b)
{
	t_pattern	ptrn;

	ptrn.type = STRIPE;
	ptrn.a = a;
	ptrn.b = b;
	ptrn.transform = matrix4_identity();
	ptrn.inverse_transform = ptrn.transform;
	ptrn.inverse_transpose = ptrn.transform;
	return (ptrn);
}

t_color	stripe_at(t_pattern pattern, t_point p)
{
	if (p.x >= 0)
	{
		if ((int)p.x % 2 == 0)
			return (pattern.a);
		else
			return (pattern.b);
	}
	else
	{
		if ((int)floor(p.x) % 2 == 0)
			return (pattern.a);
		else
			return (pattern.b);
	}
}

t_color	stripe_at_object(t_pattern ptrn, t_object *obj, t_point p)
{
	t_point	obj_point;
	t_point	ptrn_point;

	obj_point = matrix4_and_tuple_multiply(obj->inverse_transform, p);
	ptrn_point = matrix4_and_tuple_multiply(ptrn.inverse_transform, obj_point);
	return (stripe_at(ptrn, ptrn_point));
}
