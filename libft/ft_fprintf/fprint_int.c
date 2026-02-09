/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fprint_int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 14:01:56 by anpollan          #+#    #+#             */
/*   Updated: 2026/02/09 14:01:57 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	fprint_int(va_list *args, int file)
{
	int		n;
	char	*str;
	int		bytes;
	int		i;

	i = 0;
	bytes = 0;
	n = va_arg(*args, int);
	str = ft_itoa(n);
	if (!str)
		return (-1);
	while (str[i])
		i++;
	bytes = write(file, str, i);
	free(str);
	return (bytes);
}
