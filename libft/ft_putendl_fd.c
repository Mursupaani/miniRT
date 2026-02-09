/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 13:56:06 by anpollan          #+#    #+#             */
/*   Updated: 2026/02/09 13:56:07 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	size_t	s_len;
	char	new_line;

	new_line = '\n';
	if (s)
	{
		s_len = ft_strlen(s);
		write(fd, s, s_len);
	}
	write(fd, &new_line, 1);
}
