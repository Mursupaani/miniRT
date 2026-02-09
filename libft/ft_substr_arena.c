/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr_arena.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 13:52:30 by anpollan          #+#    #+#             */
/*   Updated: 2026/02/09 13:52:31 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr_empty_arena(t_arena *arena)
{
	char	*res;

	res = arena_alloc(arena, 1);
	if (!res)
		return (NULL);
	res[0] = '\0';
	return (res);
}

char	*ft_substr_arena(
	char const *s, unsigned int start, size_t len, t_arena *arena)
{
	char	*res;
	size_t	s_len;
	size_t	copy_len;
	size_t	available;

	s_len = 0;
	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_substr_empty_arena(arena));
	available = (s_len - start);
	if (len < available)
		copy_len = len;
	else
		copy_len = available;
	res = arena_alloc(arena, copy_len + 1);
	if (!res)
		return (NULL);
	ft_strlcpy(res, s + start, copy_len + 1);
	return (res);
}
