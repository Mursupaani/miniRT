/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 10:38:13 by anpollan          #+#    #+#             */
/*   Updated: 2025/11/06 18:00:02 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <math.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include "libft.h"
# include "MLX42/MLX42.h"
# include "MLX42/MLX42_Int.h"

# ifndef EPSILON
#  define EPSILON 0.00001
# endif

typedef struct s_vector3
{
	float	x;
	float	y;
	float	z;
}	t_vector3;

typedef struct s_tuple3
{
	float	x;
	float	y;
	float	z;
	float	w;
}	t_tuple3;

typedef struct s_app
{
	int			monitor_width;
	int			monitor_height;
	mlx_t		*mlx;
	mlx_image_t	*img;
}	t_app;

// App initialize and management:
t_app	*initialize_app(void);

// Memory handling and exit:
void	free_app_memory(t_app *app);
void	free_memory_and_exit(t_app *app);
void	free_memory_and_error_exit(t_app *app);

// Math utils:
bool	floats_are_equal(float a, float b);

#endif
