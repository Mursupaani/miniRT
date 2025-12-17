/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhana <juhana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 15:12:30 by anpollan          #+#    #+#             */
/*   Updated: 2025/12/17 15:43:38 by juhana           ###   ########.fr       */
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

void	parse_error(char *message, t_app *app)
{
	ft_putstr_fd("Error\n", 2);
	ft_putendl_fd(message, 2);
	exit_and_free_memory(ERROR_PARSING, app);
}
