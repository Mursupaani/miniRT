/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 20:35:47 by anpollan          #+#    #+#             */
/*   Updated: 2026/01/16 20:35:59 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_pattern	texture_map(t_pattern ptrn, t_uv_map (*uv_map)(t_point))
{
	ptrn.uv_pattern.uv_map = uv_map;
	return (ptrn);
}
