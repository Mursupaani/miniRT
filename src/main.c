/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 10:35:14 by anpollan          #+#    #+#             */
/*   Updated: 2025/11/24 11:12:59 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(int ac, char **av)
{
	t_app	*app;

	if (ac != 2)
		exit_and_free_memory(ERROR_NO_INPUT_FILE, NULL);
	// test_tuples();
	// test_matrices();
	test_transformation();
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
