/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv_checkers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 13:18:13 by anpollan          #+#    #+#             */
/*   Updated: 2025/12/25 20:58:02 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	uv_pattern_at(t_uv_ptrn ptrn, double u, double v)
{
	double	u2;
	double	v2;

	u2 = round(u * ptrn.width);
	v2 = round(v * ptrn.height);
	if ((int)(u2 + v2) % 2 == 0)
		return (ptrn.a);
	else
		return (ptrn.b);
}

t_uv_ptrn	uv_checkers(double w, double h, t_color a, t_color b)
{
	t_uv_ptrn	ptrn;

	ptrn.width = w;
	ptrn.height = h;
	ptrn.a = a;
	ptrn.b = b;
	return (ptrn);
}
