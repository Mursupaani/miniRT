/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 14:00:10 by anpollan          #+#    #+#             */
/*   Updated: 2026/02/09 14:00:11 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	dispatch_specifier(char spec, va_list *args)
{
	int					j;
	const t_specifier	specifiers[] = {
	{'c', print_char},
	{'s', print_string},
	{'p', print_pointer},
	{'d', print_int},
	{'i', print_int},
	{'u', print_unsigned},
	{'x', print_hex_lower},
	{'X', print_hex_upper},
	{'\0', NULL}
	};

	j = 0;
	while (specifiers[j].specifier)
	{
		if (specifiers[j].specifier == spec)
			return (specifiers[j].handler(args));
		j++;
	}
	write(1, &spec, 1);
	return (1);
}

static int	handle_format(const char *format, va_list *args)
{
	int		i;
	int		count;
	int		written_bytes;

	i = 0;
	count = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			written_bytes = dispatch_specifier(format[++i], args);
			if (written_bytes == -1)
				return (-1);
			count += written_bytes;
		}
		else
		{
			written_bytes = write(1, &format[i], 1);
			if (written_bytes == -1)
				return (-1);
			count += written_bytes;
		}
		i++;
	}
	return (count);
}

int	ft_printf(const char *format, ...)
{
	int		count;
	va_list	args;

	if (format == NULL)
		return (-1);
	va_start(args, format);
	count = handle_format(format, &args);
	va_end(args);
	return (count);
}
