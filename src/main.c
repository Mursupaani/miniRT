/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhana <juhana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 10:35:14 by anpollan          #+#    #+#             */
/*   Updated: 2026/01/30 15:38:39 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file main.c
 * @brief Main entry point for the ray tracing application.
 *
 * This file contains the main() function which orchestrates the
 * application's lifecycle. It is responsible for:
 * 1. Validating command-line arguments.
 * 2. Initializing the application state and MLX.
 * 3. Calling the parser to load the scene file.
 * 4. Starting the main event loop (mlx_loop).
 * 5. Handling cleanup and memory freeing on exit.
 *
 * Defines:
 * - main()
 */
#include "minirt.h"

int	main(int ac, char **av)
{
	t_app	*app;

	if (ac != 2)
		exit_and_free_memory(ERROR_NO_INPUT_FILE, NULL);
	app = initialize_app();
	parse_rt_file(av, app);
	launch_render(app);
	mlx_loop(app->mlx);
	free_app_memory(app);
	return (0);
}
