/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcastrat <mcastrat@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 10:41:29 by mcastrat          #+#    #+#             */
/*   Updated: 2025/12/22 14:19:37 by mcastrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static char	*extract_texture_path(char *line)
{
	char	*path_texture;

	path_texture = ft_strtrim(line + 3, " \t\n\r\v\f");
	if (!path_texture || !*path_texture)
	{
		printf("Error\nEmpty texture path\n");
		if (path_texture)
			free(path_texture);
		exit(EXIT_FAILURE);
	}
	return (path_texture);
}

static void	validate_texture_file(char *path_texture)
{
	int	fd;

	fd = open(path_texture, O_RDONLY);
	if (fd == -1)
	{
		printf("Error\nTexture %s not found\n", path_texture);
		free(path_texture);
		exit(EXIT_FAILURE);
	}
	close(fd);
}

static void	store_texture(char *line, char *path_texture, t_walls *walls)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		walls->north = path_texture;
	else if (ft_strncmp(line, "SO ", 3) == 0)
		walls->south = path_texture;
	else if (ft_strncmp(line, "WE ", 3) == 0)
		walls->west = path_texture;
	else if (ft_strncmp(line, "EA ", 3) == 0)
		walls->east = path_texture;
}

void	parse_textures(char *line, t_walls *walls)
{
	char	*path_texture;

	path_texture = extract_texture_path(line);
	validate_texture_file(path_texture);
	store_texture(line, path_texture, walls);
}

void	init_textures(t_walls *walls)
{
	int	i;

	walls->north = NULL;
	walls->south = NULL;
	walls->west = NULL;
	walls->east = NULL;
	i = 0;
	while (i < 3)
	{
		walls->floor[i] = -1;
		walls->ceiling[i] = -1;
		i++;
	}
}