/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 13:56:20 by anpollan          #+#    #+#             */
/*   Updated: 2026/02/09 13:56:22 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	val ;
	unsigned char	*ptr;

	i = 0;
	val = (unsigned char)c;
	ptr = (unsigned char *)s;
	while (i < n)
	{
		ptr[i] = val;
		i++;
	}
	return (s);
}
