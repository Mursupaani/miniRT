/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 10:38:13 by anpollan          #+#    #+#             */
/*   Updated: 2025/11/07 18:27:52 by anpollan         ###   ########.fr       */
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

// FIXME: Find best value for epsilon! 0.00001 doesn't work like in guide
# ifndef EPSILON
#  define EPSILON 1e-4f
# endif

typedef struct s_tuple
{
	float	x;
	float	y;
	float	z;
	float	w;
}	t_tuple;
typedef t_tuple	t_vector;
typedef t_tuple	t_point;

//FIXME: Testing
typedef struct s_proj
{
	t_point		*p;
	t_vector	*v;
}	t_proj;

typedef struct s_env
{
	t_vector	*g;
	t_vector	*w;
}	t_env;
//FIXME: Testing

typedef struct s_app
{
	int			monitor_width;
	int			monitor_height;
	mlx_t		*mlx;
	mlx_image_t	*img;
}	t_app;

// Debug
void		print_tuple(t_tuple *tuple);
t_proj		*tick(t_env *env, t_proj *proj);
void		projectile(t_app *app);

// App initialize and management:
t_app		*initialize_app(void);

// Memory handling and exit:
void		free_app_memory(t_app *app);
void		free_memory_and_exit(t_app *app);
void		free_memory_and_error_exit(t_app *app);

// Tuples (vectors, points):
t_tuple		*new_tuple(float x, float y, float z, float w);
t_vector	*new_vector(float x, float y, float z);
t_point		*new_point(float x, float y, float z);

// Tuple math:
t_tuple		*tuple_sum(t_tuple *a, t_tuple *b);
t_tuple		*tuple_subtract(t_tuple *a, t_tuple *b);
t_tuple		*tuple_scale_multiply(t_tuple *tuple, float scalar);
t_tuple		*tuple_scale_divide(t_tuple *tuple, float divider);
t_tuple		*tuple_negate(t_tuple *tuple);

// Vector math:
float		vector_magnitude(t_tuple *vector);
t_vector	*vector_normalize(t_vector *vector);
float		vector_dot_product(t_vector *a, t_vector *b);
t_vector	*vector_cross_product(t_vector *a, t_vector *b);

// Tuple utils:
bool		tuples_are_equal(t_tuple *a, t_tuple *b);

// Math utils:
bool		floats_are_equal(float a, float b);

// Rendering utils
bool		pixel_fits_image(float x, float y, t_app *app);

#endif
