/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 15:12:30 by anpollan          #+#    #+#             */
/*   Updated: 2025/11/10 15:24:15 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	skip_whitespace(char **str)
{
	while (ft_isspace(**str))
		(*str)++;
}

bool	filetype_is_valid(char *filename)
{
	int	strlen;

	if (!filename)
		return (false);
	strlen = ft_strlen(filename);
	if (strlen >= 4 && ft_strncmp(".rt", &filename[strlen - 3], 3) == 0)
		return (true);
	return (false);
}
