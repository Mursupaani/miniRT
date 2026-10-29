/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_and_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhana <juhana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 17:48:50 by anpollan          #+#    #+#             */
/*   Updated: 2026/01/16 20:31:15 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	*memory_alloc_error(atomic_int *err)
{
	*err = 1;
	return (NULL);
}

void	exit_and_free_memory(int exit_code, t_app *app)
{
	if (exit_code == ERROR_NO_INPUT_FILE)
		ft_fprintf(STDERR_FILENO, "Error\nPlease pass .rt file as argument.\n");
	else if (exit_code == ERROR_MLX_INIT)
		ft_fprintf(STDERR_FILENO, "Error\nFailed to initialize MLX\n");
	else if (exit_code == ERROR_MLX_IMG_INIT)
		ft_fprintf(STDERR_FILENO, "Error\nFailed to initialize MLX image\n");
	else if (exit_code == ERROR_INVALID_FILE_TYPE)
		ft_fprintf(STDERR_FILENO, "Error\nInvalid filetype\n");
	else if (exit_code == ERROR_OPEN)
		ft_fprintf(STDERR_FILENO, "Error\nCan't open file\n");
	else if (exit_code == ERROR_SCENE)
		ft_fprintf(STDERR_FILENO, "Error\nCan't create scene\n");
	else if (exit_code == ERROR_PARSING)
		ft_fprintf(STDERR_FILENO, "Error\nFailed to parse file contents\n");
	else if (exit_code == ERROR_THREADS)
		ft_fprintf(STDERR_FILENO, "Error\nThread creation failed\n");
	else if (exit_code == ERROR_UI)
		ft_fprintf(STDERR_FILENO, "Error\nUI failure\n");
	else if (exit_code == ERROR_THREAD_MEMORY)
		ft_fprintf(STDERR_FILENO, "Error\nThread memory error\n");
	else if (exit_code != 0)
		ft_fprintf(STDERR_FILENO, "Error\n");
	if (app)
		free_app_memory(app);
	exit(exit_code);
}
