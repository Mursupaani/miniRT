/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 10:18:46 by anpollan          #+#    #+#             */
/*   Updated: 2025/12/16 17:17:50 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	color(double r, double g, double b)
{
	t_color	color;

	color.r = r;
	color.g = g;
	color.b = b;
	return (color);
}

t_color255	color255(
		unsigned char r, unsigned char g, unsigned char b)
{
	t_color255	color255;

	color255.r = r;
	color255.g = g;
	color255.b = b;
	return (color255);
}
