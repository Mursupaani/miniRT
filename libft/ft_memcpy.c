/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 13:56:38 by anpollan          #+#    #+#             */
/*   Updated: 2026/02/09 13:56:39 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t				i;
	const unsigned char	*s1;
	unsigned char		*s2;

	i = 0;
	s1 = (unsigned char *)src;
	s2 = (unsigned char *)dest;
	while (i < n)
	{
		s2[i] = s1[i];
		i++;
	}
	return (dest);
}
