/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhana <juhana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 10:35:14 by anpollan          #+#    #+#             */
/*   Updated: 2025/11/21 14:56:32 by juhana           ###   ########.fr       */
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
	projectile(app);
	mlx_loop(app->mlx);
	join_threads(app->threads, THREADS);
	free_app_memory(app);
	test_tuples();
	test_matrices();
	// app = initialize_app();
	// float m1[4][4] = {{1, 2, 3, 4}, {2, 4, 4, 2}, {8, 6, 4, 1}, {0, 0, 0, 1}};
	// print_matrix4(m1);
	// parse_rt_file(av, app);
	// projectile(app);
	// mlx_loop(app->mlx);
	// free_app_memory(app);
	return (0);
	//FIXME: remove this
	(void)app;
	(void)av;
}
