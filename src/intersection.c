#include "minirt.h"

t_intersection	*intersection_new(float t, t_object *object)
{
	t_intersection	*new_node;

	new_node = malloc(sizeof(t_intersection));
	if (!new_node)
		return (NULL);
	new_node->t = t;
	new_node->object = object;
	new_node->next = NULL;
	return (new_node);
}

t_intersection	*intersection_hit(t_intersection *xs)
{
	t_intersection	*closest;
	t_intersection	*current;

	closest = NULL;
	current = xs;
	while (current)
	{
		if (current->t >= 0)
		{
			if (closest == NULL || current->t < closest->t)
				closest = current;
		}
		current = current->next;
	}
	return (closest);
}

static t_intersection	*intersection_lstlast_xs(t_intersection *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	intersection_add_back(t_intersection **lst, t_intersection *new)
{
	t_intersection	*last;

	if (!lst || !new)
		return ;
	new->next = NULL;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = intersection_lstlast_xs(*lst);
	if (last)
		last->next = new;
}

void	intersection_free(t_intersection *lst)
{
	t_intersection	*next;

	if (!lst)
		return ;
	while (lst)
	{
		next = lst->next;
		// HOX! this probably can't be in the prod version
		//free(lst->object);
		free(lst);
		lst = next;
	}
}
