/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 10:35:14 by anpollan          #+#    #+#             */
/*   Updated: 2025/11/07 18:27:45 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(int ac, char **av)
{
	t_app	*app;

	if (ac != 2)
	{
		printf("Please pass a .rt file as an argument.\n");
		return (1);
	}
	app = initialize_app();
	projectile(app);
	mlx_loop(app->mlx);
	(void)av;
	return (0);
}
