/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 16:03:27 by anpollan          #+#    #+#             */
/*   Updated: 2026/01/01 17:02:25 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	calculate_pixel_offset(int x, int y, mlx_texture_t *texture)
{
	return (y * texture->bytes_per_pixel * texture->width
			+ x * texture->bytes_per_pixel);
}
