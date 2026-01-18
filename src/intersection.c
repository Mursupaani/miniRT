/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 18:28:15 by anpollan          #+#    #+#             */
/*   Updated: 2025/12/19 16:39:53 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_intersections	*malloc_intersections(int xs_count, atomic_int *err)
{
	t_intersections	*xs;

	xs = malloc(sizeof(t_intersections));
	if (!xs)
		return (memory_alloc_error(err));
	xs->arr = malloc(sizeof(t_intersection) * xs_count);
	if (!xs->arr)
	{
		free(xs);
		return (memory_alloc_error(err));
	}
	return (xs);
}

t_intersection	intersection(double t, t_object *object)
{
	t_intersection	intersection;

	intersection.t = t;
	intersection.object = object;
	return (intersection);
}

t_intersection	hit(t_intersections *xs)
{
	int				i;
	t_intersection	closest;

	i = -1;
	closest = (t_intersection){DBL_MAX, NULL};
	while (++i < xs->count)
	{
		if (xs->arr[i].t >= 0)
		{
			if (xs->arr[i].t < closest.t)
				closest = xs->arr[i];
		}
	}
	return (closest);
}

//FIXME: Old intersection functions using linked list

// t_intersection	*intersection_new(double t, t_object *object)
// {
// 	t_intersection	*new_node;
//
// 	new_node = malloc(sizeof(t_intersection));
// 	if (!new_node)
// 		return (NULL);
// 	new_node->t = t;
// 	new_node->object = object;
// 	new_node->next = NULL;
// 	return (new_node);
// }
//
// t_intersection	*intersection_hit(t_intersection *xs)
// {
// 	t_intersection	*closest;
// 	t_intersection	*current;
//
// 	closest = NULL;
// 	current = xs;
// 	while (current)
// 	{
// 		if (current->t >= 0)
// 		{
// 			if (closest == NULL || current->t < closest->t)
// 				closest = current;
// 		}
// 		current = current->next;
// 	}
// 	return (closest);
// }
//
// static t_intersection	*intersection_lstlast_xs(t_intersection *lst)
// {
// 	if (!lst)
// 		return (NULL);
// 	while (lst->next)
// 		lst = lst->next;
// 	return (lst);
// }
//
// void	intersection_add_back(t_intersection **lst, t_intersection *new)
// {
// 	t_intersection	*last;
//
// 	if (!lst || !new)
// 		return ;
// 	new->next = NULL;
// 	if (!*lst)
// 	{
// 		*lst = new;
// 		return ;
// 	}
// 	last = intersection_lstlast_xs(*lst);
// 	if (last)
// 		last->next = new;
// }
//
// void	intersection_free(t_intersection *lst)
// {
// 	t_intersection	*next;
//
// 	if (!lst)
// 		return ;
// 	while (lst)
// 	{
// 		next = lst->next;
// 		free(lst);
// 		lst = next;
// 	}
// }
