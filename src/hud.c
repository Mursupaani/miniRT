/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 15:43:04 by anpollan          #+#    #+#             */
/*   Updated: 2026/01/16 15:55:32 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "minirt.h"

static int	string_to_buf(char *str, char *buf, int i, int size)
{
	int	j;

	if (!str || !buf)
		return INT_MIN;
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
	i = string_to_buf("FOV: ", hud, i, size);
	i += ft_itoa_to_buf(roundf(c->fov * 180 / M_PI), &hud[i], 256);
	i = string_to_buf("\n", hud, i, size);
	return (i);
}

void	print_hud(t_app *app)
{
	mlx_t	*mlx;
	char	hud[2048];
	int		i;

	if (app->hud)
		mlx_delete_image(app->mlx, app->hud);
	mlx = app->mlx;
	i = 0;
	i = fov_to_buffer(app->scene->camera, hud, i, 2048);
	app->hud = mlx_put_string(mlx, hud, 10, 10);
}
