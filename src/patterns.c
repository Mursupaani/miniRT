/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   patterns.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 12:06:15 by anpollan          #+#    #+#             */
/*   Updated: 2025/12/16 12:48:45 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_pattern	stripe_pattern(t_color a, t_color b)
{
	return ((t_pattern){a, b});
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
