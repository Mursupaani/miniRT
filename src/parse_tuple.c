/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tuple.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 15:50:39 by anpollan          #+#    #+#             */
/*   Updated: 2026/01/30 15:50:40 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	parse_vector(char **str, t_vector *vec)
{
	if (!parse_double(str, &vec->x))
		return (false);
	skip_whitespace(str);
	if (**str == ',')
		(*str)++;
	if (!parse_double(str, &vec->y))
		return (false);
	skip_whitespace(str);
	if (**str == ',')
		(*str)++;
	if (!parse_double(str, &vec->z))
		return (false);
	vec->w = 0.0;
	return (true);
}

bool	parse_point(char **str, t_point *point)
{
	if (!parse_double(str, &point->x))
		return (false);
	skip_whitespace(str);
	if (**str == ',')
		(*str)++;
	if (!parse_double(str, &point->y))
		return (false);
	skip_whitespace(str);
	if (**str == ',')
		(*str)++;
	if (!parse_double(str, &point->z))
		return (false);
	point->w = 1.0;
	return (true);
}

bool	parse_color(char **str, t_color *color)
{
	int	r;
	int	g;
	int	b;

	if (!parse_int(str, &r) || r < 0 || r > 255)
		return (false);
	skip_whitespace(str);
	if (**str == ',')
		(*str)++;
	if (!parse_int(str, &g) || g < 0 || g > 255)
		return (false);
	skip_whitespace(str);
	if (**str == ',')
		(*str)++;
	if (!parse_int(str, &b) || b < 0 || b > 255)
		return (false);
	*color = color_from_color255(color255(r, g, b));
	return (true);
}
