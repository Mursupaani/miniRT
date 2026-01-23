/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhana <juhana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 00:00:00 by juhana            #+#    #+#             */
/*   Updated: 2026/01/21 11:37:42 by juhana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static bool	parse_texture_path(char **str, char *path, size_t max_len)
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

bool	parse_texture(char **str, mlx_texture_t **texture, t_app *app)
{
	char	path[256];

	skip_whitespace(str);
	if (ft_strncmp(*str, "texture:", 8) != 0)
		return (false);
	*str += 8;
	if (!parse_texture_path(str, path, 256))
	{
		parse_error("Invalid texture path", app);
		return (false);
	}
	*texture = mlx_load_png(path);
	if (!*texture)
	{
		parse_error("Failed to load texture", app);
		return (false);
	}
	return (true);
}



void	apply_texture_to_object(t_object *obj, char **line, t_app *app)
{
	mlx_texture_t	*texture;

	skip_whitespace(line);
	if (**line == '\0' || **line == '#')
		return ;
	if (parse_texture(line, &texture, app))
	{
		obj->material.pattern = uv_image(texture);
		if (obj->type == SPHERE)
			obj->material.pattern = texture_map(obj->material.pattern, spherical_map);
		else if (obj->type == CUBE)
			obj->material.pattern = texture_map(obj->material.pattern, cubic_atlas_map);
		else if (obj->type == CYLINDER)
			obj->material.pattern = texture_map(obj->material.pattern, cylindrical_map);
		else if (obj->type == CONE)
			obj->material.pattern = texture_map(obj->material.pattern, cylindrical_map);
		else if (obj->type == PLANE)
			obj->material.pattern = texture_map(obj->material.pattern, planar_map);
	}
}
