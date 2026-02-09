/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fprint_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 14:01:45 by anpollan          #+#    #+#             */
/*   Updated: 2026/02/09 14:01:46 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	fprint_string(va_list *args, int file)
{
	int		i;
	char	*str;

	i = 0;
	str = va_arg(*args, char *);
	if (str == NULL)
		return (write(file, "(null)", 6));
	while (str[i])
	{
		write(file, &str[i], 1);
		i++;
	}
	return (i);
}
