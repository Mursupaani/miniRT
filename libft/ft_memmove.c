/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 13:56:30 by anpollan          #+#    #+#             */
/*   Updated: 2026/02/09 13:56:31 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t				i;
	const unsigned char	*src_bytes;
	unsigned char		*dest_bytes;

	src_bytes = (unsigned char *)src;
	dest_bytes = (unsigned char *)dest;
	if (dest < src)
	{
		i = 0;
		while (i < n)
		{
			dest_bytes[i] = src_bytes[i];
			i++;
		}
	}
	else
	{
		i = n;
		while (i)
		{
			dest_bytes[i - 1] = src_bytes[i - 1];
			i--;
		}
	}
	return (dest);
}
