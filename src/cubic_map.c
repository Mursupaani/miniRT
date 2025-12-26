/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubic_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 20:21:43 by anpollan          #+#    #+#             */
/*   Updated: 2025/12/26 21:06:08 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_uv_ptrn	uv_align_check(void)
{
	t_uv_ptrn uv;

	uv.a = color(DBL_MIN, DBL_MIN, DBL_MIN);
	uv.b = color(DBL_MIN, DBL_MIN, DBL_MIN);
	uv.width = 0;
	uv.height = 0;
	uv.type = ALIGN_CHECK;
	uv.align.main = color(1, 1, 1);
	uv.align.ul = color(1, 0, 0);
	uv.align.ur = color(1, 1, 0);
	uv.align.bl = color(0, 1, 0);
	uv.align.br = color(0, 1, 1);
	return (uv);
}
