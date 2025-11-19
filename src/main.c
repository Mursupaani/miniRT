/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 10:35:14 by anpollan          #+#    #+#             */
/*   Updated: 2025/11/19 14:30:09 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(int ac, char **av)
{
	t_app	*app;

	if (ac != 2)
		exit_and_free_memory(ERROR_NO_INPUT_FILE, NULL);
	// app = initialize_app();
	float (*m1)[4] = malloc(sizeof(float) * (4 * 4));
	m1[0][0] = 1;
	m1[0][1] = 2;
	m1[0][2] = 3;
	m1[0][3] = 4;
	m1[1][0] = 5;
	m1[1][1] = 6;
	m1[1][2] = 7;
	m1[1][3] = 8;
	m1[2][0] = 9;
	m1[2][1] = 8;
	m1[2][2] = 7;
	m1[2][3] = 6;
	m1[3][0] = 5;
	m1[3][1] = 4;
	m1[3][2] = 3;
	m1[3][3] = 2;
	float m2[4][4] = {{-2, 1, 2, 3}, {3, 2, 1, -1}, {4, 3, 6, 5}, {1, 2, 7, 8}};
	float (*m3)[4] = multiply_matrix_4s(m1, m2);
	int i = 0;
	while (i < 4)
	{
		int j = 0;
		while (j < 4)
		{
			printf("%.0f", m3[i][j]);
			if (j < 3)
				printf(", ");
			j++;
		}
		printf("\n");
		i++;
	}
	// parse_rt_file(av, app);
	// projectile(app);
	// mlx_loop(app->mlx);
	// free_app_memory(app);
	return (0);
	//FIXME: remove this
	(void)app;
	(void)av;
}
