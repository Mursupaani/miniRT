/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhana <juhana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 10:35:14 by anpollan          #+#    #+#             */
/*   Updated: 2025/12/18 15:18:30 by anpollan         ###   ########.fr       */
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

void	test_render()
{
	t_app	*app;

	app = initialize_app();
	build_chapter7_world(app);
	launch_render(app);
	mlx_image_to_window(app->mlx, app->img, 0, 0);
	mlx_loop(app->mlx);
}

int	main(int ac, char **av)
{
	t_app	*app;

	(void)ac;
	(void)av;
	//if (ac != 2)
		//exit_and_free_memory(ERROR_NO_INPUT_FILE, NULL);
	// app = initialize_app();
	// run_tests();
	test_render();
	// parse_rt_file(av, app);
	// launch_render(app);
	// mlx_image_to_window(app->mlx, app->img, 0, 0);
	// mlx_loop(app->mlx);
	// join_threads(app->threads, THREADS);
	// free_app_memory(app);
	return (0);
	//FIXME: remove this
	(void)app;
	(void)av;
}
