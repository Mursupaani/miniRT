/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 18:20:23 by anpollan          #+#    #+#             */
/*   Updated: 2025/11/07 18:24:52 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	pixel_fits_image(double x, double y, t_app *app)
{
	return (x >= 0 && x <= app->img->width
		&& y >= 0 && y <= app->img->height);
}
