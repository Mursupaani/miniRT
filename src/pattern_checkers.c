/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern_checkers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 18:49:53 by anpollan          #+#    #+#             */
/*   Updated: 2025/12/16 19:33:16 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_pattern	checkers_pattern(t_color a, t_color b)
{
	return (create_pattern(CHECKERS, a, b));
	// t_pattern	checker;
	//
	// checker.type = CHECKER;
	// checker.a = a;
	// checker.b = b;
	// checker.transform = matrix4_identity();
	// checker.inverse_transform = checker.transform;
	// checker.inverse_transpose = checker.transform;
	// return (checker);
}

t_color	checkers_at(t_pattern gradient, t_point p)
{
	if ((int)(floor(p.x) + floor(p.y) + floor(p.z)) % 2 == 0)
		return (gradient.a);
	else
		return (gradient.b);
}
