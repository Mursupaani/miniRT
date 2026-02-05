/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 15:43:04 by anpollan          #+#    #+#             */
/*   Updated: 2026/02/02 21:19:50 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	string_to_buf(char *str, char *buf, int i, int size)
{
	int	j;

	j = 0;
	while (i < size - 1 && str[j])
	{
		buf[i] = str[j];
		i++;
		j++;
	}
	buf[i] = '\0';
	return (i);
}

static int	fov_to_buffer(t_camera *c, char *hud, int i, int size)
{
	i = string_to_buf("FOV: ", hud, i, size - i);
	i += ft_itoa_to_buf(roundf(rad_to_deg(c->fov)), &hud[i], size - i);
	return (i);
}

static int	pixelation_and_aa_to_buffer(t_app *app, char *hud, int i, int size)
{
	if (app->pixelate)
	{
		i = string_to_buf("    Pixelation: ", hud, i, size - i);
		i += ft_itoa_to_buf(app->current_pixelate_scale, &hud[i], size - i);
	}
	else
		i = string_to_buf("    Anti-aliasing", hud, i, size - i);
	return (i);
}

static int	ready_percent_to_buffer(t_app *app, char *hud, int i, int size)
{
	i = string_to_buf("    Ready: ", hud, i, size - i);
	i += ft_itoa_to_buf(app->ready_percent, &hud[i], size - i);
	i = string_to_buf("%", hud, i, size - i);
	if (app->ready_percent == 0)
		i = string_to_buf("  ", hud, i, size - i);
	else if (app->ready_percent != 100)
		i = string_to_buf(" ", hud, i, size - i);
	return (i);
}

void	print_hud(t_app *app)
{
	mlx_t	*mlx;
	char	hud[128];
	int		i;

	if (app->hud)
		mlx_delete_image(app->mlx, app->hud);
	mlx = app->mlx;
	i = 0;
	i = fov_to_buffer(app->scene->camera, hud, i, 128);
	i = ready_percent_to_buffer(app, hud, i, 128);
	i = pixelation_and_aa_to_buffer(app, hud, i, 128);
	hud[i] = '\0';
	app->hud = mlx_put_string(mlx, hud, 10, 10);
}
