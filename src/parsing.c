/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 17:33:57 by anpollan          #+#    #+#             */
/*   Updated: 2025/11/10 16:37:43 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	parse_line(char *line, t_app *app)
{
	char	**split;

	split = ft_split(line, ' ');
	if (!split)
		return ;
	(void)app;
}

static void	parse_rt_file_lines(int fd, t_app *app)
{
	char	*line;

	line = get_next_line(fd);
	if (!line)
		exit_and_free_memory(ERROR_PARSING, app);
	while (line)
	{
		parse_line(line, app);
		free(line);
		line = get_next_line(fd);
	}
}

static bool	filetype_is_valid(char *filename)
{
	int	strlen;

	if (!filename)
		return (false);
	strlen = ft_strlen(filename);
	if (strlen >= 4 && ft_strncmp(".rt", &filename[strlen - 3], 3) == 0)
		return (true);
	return (false);
}

void	parse_rt_file(char **av, t_app *app)
{
	int	fd;

	if (!filetype_is_valid(av[1]))
		exit_and_free_memory(ERROR_INVALID_FILE_TYPE, app);
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		exit_and_free_memory(ERROR_OPEN, app);
	app->scene = ft_calloc(1, sizeof(t_scene));
	if (!app->scene)
		exit_and_free_memory(ERROR_SCENE, app);
	parse_rt_file_lines(fd, app);
	close(fd);
}
