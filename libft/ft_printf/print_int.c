/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 14:00:33 by anpollan          #+#    #+#             */
/*   Updated: 2026/02/09 14:00:34 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	print_int(va_list *args)
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
	bytes = write(1, str, i);
	free(str);
	return (bytes);
}
