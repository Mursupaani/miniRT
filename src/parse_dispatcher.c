/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dispatcher.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 15:39:27 by anpollan          #+#    #+#             */
/*   Updated: 2026/01/30 15:39:28 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	set_scene_ambient_values(t_app *app)
{
	t_object	**objects;
	double		ambient;
	int			i;

	objects = app->scene->objects;
	if (!objects)
		return ;
	ambient = app->scene->light->ambient_ratio;
	i = -1;
	while (objects[++i])
	{
		if (objects[i]->material.ambient == -1)
			objects[i]->material.ambient = ambient;
	}
}

static void	parse_line(char *line, t_app *app)
{
	skip_whitespace(&line);
	if (!*line || *line == '#')
		return ;
	if (*line == 'A' && ft_isspace(*(line + 1)))
		parse_ambient_component(&line, app);
	else if (*line == 'C' && ft_isspace(*(line + 1)))
		parse_camera(&line, app);
	else if (*line == 'L' && ft_isspace(*(line + 1)))
		parse_light(&line, app);
	else if (line[0] == 's' && line[1] == 'p' && ft_isspace(line[2]))
		parse_sphere(&line, app);
	else if (line[0] == 'p' && line[1] == 'l' && ft_isspace(line[2]))
		parse_plane(&line, app);
	else if (line[0] == 'c' && line[1] == 'y' && ft_isspace(line[2]))
		parse_cylinder(&line, app);
	else if (line[0] == 'c' && line[1] == 'u' && ft_isspace(line[2]))
		parse_cube(&line, app);
	else if (line[0] == 'c' && line[1] == 'o' && ft_isspace(line[2]))
		parse_cone(&line, app);
	else
		parse_error("Unknown element type", app);
	skip_whitespace(&line);
	if (*line != '\0' && *line != '#')
		parse_error("Unexpted element order or type", app);
}

static void	parse_rt_file_lines(int fd, t_app *app)
{
	char	*line;

	app->parsing_success = true;
	line = get_next_line(fd);
	while (line)
	{
		parse_line(line, app);
		free(line);
		line = get_next_line(fd);
	}
	if (app->parsing_success != true)
		exit_and_free_memory(ERROR_PARSING, app);
}

static void	validate_scene(t_app *app)
{
	if (!app->scene->camera)
		parse_error("No camera defined in scene", app);
	if (!app->scene->light)
		parse_error("No light defined in scene", app);
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
	validate_scene(app);
	set_scene_ambient_values(app);
}
