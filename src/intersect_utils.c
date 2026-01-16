/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 18:36:56 by anpollan          #+#    #+#             */
/*   Updated: 2026/01/16 19:41:24 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	copy_intersections(
		t_intersections *xs, t_intersections *temp,
		t_intersection new, int count)
{
	int	i;

	i = 0;
	while (temp && i < count)
	{
		xs->arr[i] = temp->arr[i];
		i++;
	}
	xs->arr[i] = new;
	xs->count = count + 1;
}

t_intersections	*add_intersection_to_intersections(
		t_intersection new, t_intersections *xs)
{
	t_intersections	*temp;
	int				count;

	temp = xs;
	if (temp == NULL)
		count = 0;
	else
		count = temp->count;
	xs = ft_calloc(1, sizeof(t_intersections));
	if (!xs)
	{
		free_intersections(&temp);
		return (NULL);
	}
	xs->arr = malloc(sizeof(t_intersection) * (count + 1));
	if (!xs->arr)
	{
		free_intersections(&temp);
		free_intersections(&xs);
		return (NULL);
	}
	copy_intersections(xs, temp, new, count);
	free_intersections(&temp);
	return (xs);
}

t_coefs	calculate_cone_coefs(t_ray local_ray)
{
	t_coefs	coefs;

	coefs.a = pow(local_ray.direction.x, 2) - pow(local_ray.direction.y, 2)
		+ pow(local_ray.direction.z, 2);
	coefs.b = 2 * local_ray.origin.x * local_ray.direction.x
		- 2 * local_ray.origin.y * local_ray.direction.y
		+ 2 * local_ray.origin.z * local_ray.direction.z;
	coefs.c = (pow(local_ray.origin.x, 2)
			- pow(local_ray.origin.y, 2)
			+ pow(local_ray.origin.z, 2));
	return (coefs);
}
