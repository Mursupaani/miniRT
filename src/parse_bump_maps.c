/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bump_maps.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhana <juhana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 00:00:00 by juhana            #+#    #+#             */
/*   Updated: 2026/01/21 11:37:40 by juhana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static bool	parse_bump_map_path(char **str, char *path, size_t max_len)
{
	size_t	i;

	i = 0;
	skip_whitespace(str);
	while (**str && !ft_isspace(**str) && i < max_len - 1)
	{
		path[i] = **str;
		(*str)++;
		i++;
	}
	path[i] = '\0';
	return (i > 0);
}

bool	parse_bump_map(char **str, t_bump_map *bump_map, t_app *app)
{
	char	path[256];

	skip_whitespace(str);
	if (ft_strncmp(*str, "bump:", 5) != 0)
		return (false);
	*str += 5;
	if (!parse_bump_map_path(str, path, 256))
	{
		parse_error("Invalid bump map path", app);
		return (false);
	}
	bump_map->bump_map = mlx_load_png(path);
	if (!bump_map->bump_map)
	{
		parse_error("Failed to load bump map", app);
		return (false);
	}
	bump_map->has_bump_map = true;
	return (true);
}

void	apply_bump_map_to_object(t_object *obj, char **line, t_app *app)
{
	skip_whitespace(line);
	if (**line == '\0' || **line == '#')
		return ;
	if (parse_bump_map(line, &obj->bump_map, app))
	{
		if (obj->type == SPHERE)
			obj->bump_map.uv_map = spherical_map;
		else if (obj->type == CUBE)
			obj->bump_map.uv_map = cubic_map;
		else if (obj->type == CYLINDER)
			obj->bump_map.uv_map = cylindrical_map;
		else if (obj->type == CONE)
			obj->bump_map.uv_map = cylindrical_map;
		else if (obj->type == PLANE)
			obj->bump_map.uv_map = planar_map;
	}
}
