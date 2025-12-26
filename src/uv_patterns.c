/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv_patterns.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 13:16:57 by anpollan          #+#    #+#             */
/*   Updated: 2025/12/25 20:57:45 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_texture_map	texture_map(t_uv_ptrn ptrn, t_uv_map uv_map)
{
	t_texture_map	map;

	map.pattern = ptrn;
	map.uv_map = uv_map;
	return (map);
}

// t_color	handle_uv_pattern(t_pattern ptrn, t_point ptrn_point)
// {
// 	if (ptrn.style == CHECKER)
// 		checkers_pattern
// }
