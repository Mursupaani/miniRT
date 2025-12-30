/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv_checkers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 13:18:13 by anpollan          #+#    #+#             */
/*   Updated: 2025/12/26 20:40:38 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_pattern	uv_checkers(double w, double h, t_color a, t_color b)
{
	t_pattern		ptrn;

	ptrn = create_pattern(MAP, a, b);
	ptrn.uv_pattern.type = UV_CHECKERS;
	ptrn.uv_pattern.width = w;
	ptrn.uv_pattern.height = h;
	return (ptrn);
}
