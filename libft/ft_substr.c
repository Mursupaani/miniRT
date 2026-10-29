/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 13:52:20 by anpollan          #+#    #+#             */
/*   Updated: 2026/02/09 13:52:21 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr_empty(void)
{
	char	*res;

	res = malloc(1);
	if (!res)
		return (NULL);
	res[0] = '\0';
	return (res);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
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
		return (ft_substr_empty());
	available = (s_len - start);
	if (len < available)
		copy_len = len;
	else
		copy_len = available;
	res = malloc(copy_len + 1);
	if (!res)
		return (NULL);
	ft_strlcpy(res, s + start, copy_len + 1);
	return (res);
}
