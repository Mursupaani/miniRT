/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fprint_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 14:01:30 by anpollan          #+#    #+#             */
/*   Updated: 2026/02/09 14:01:31 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	fprint_char(va_list *args, int file)
{
	char	c;

	c = (char)va_arg(*args, int);
	return (write(file, &c, 1));
}
