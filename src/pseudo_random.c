/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pseudo_random.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 15:50:02 by anpollan          #+#    #+#             */
/*   Updated: 2026/01/30 15:50:03 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static unsigned int	hash_coords(unsigned int x, unsigned int y, unsigned int s)
{
	unsigned int	hash;

	hash = x * 374761393U;
	hash += y * 668265263U;
	hash ^= s * 1274126177U;
	hash = (hash ^ (hash >> 13)) * 1274126177U;
	return (hash ^ (hash >> 16));
}

double	pseudo_random(unsigned int x, unsigned int y, unsigned int s)
{
	return ((double)(hash_coords(x, y, s) & 0xFFFFFF) / 16777216.0);
}
