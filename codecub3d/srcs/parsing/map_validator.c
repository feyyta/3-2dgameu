/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcastrat <mcastrat@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 14:52:33 by mcastrat          #+#    #+#             */
/*   Updated: 2025/12/25 18:08:56 by mcastrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	is_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n'
			&& line[i] != '1' && line[i] != '0' && line[i] != 'N'
			&& line[i] != 'S' && line[i] != 'E' && line[i] != 'W')
			return (0);
		i++;
	}
	return (1);
}

static int	check_border(t_grid *grid, int x, int y)
{
	if (y == 0 || y == grid->height - 1 || x == 0 || x == grid->width - 1)
		return (printf("Error\nMap not closed at borders\n"), 0);
	if (grid->grid[y - 1][x] == ' ' || grid->grid[y + 1][x] == ' '
		|| grid->grid[y][x - 1] == ' ' || grid->grid[y][x + 1] == ' ')
		return (printf("Error\nMap not properly enclosed\n"), 0);
	return (1);
}

int	validate_map_closed(t_grid *grid)
{
	int	x;
	int	y;

	y = 0;
	while (y < grid->height)
	{
		x = 0;
		while (x < grid->width)
		{
			if (grid->grid[y][x] == '0')
			{
				if (!check_border(grid, x, y))
					return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}

int	validate_textures(t_walls *walls)
{
	if (!walls->north || !walls->south
		|| !walls->west || !walls->east)
		return (printf("Error\nMissing texture\n"), 0);
	if (walls->floor[0] == -1 || walls->ceiling[0] == -1)
		return (printf("Error\nMissing floor or ceiling color\n"), 0);
	return (1);
}

int	parse_config_line(char *line, t_walls *walls)
{
	if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0)
		return (parse_textures(line, walls), 1);
	else if (ft_strncmp(line, "F ", 2) == 0)
		return (parse_color(line, walls->floor), 1);
	else if (ft_strncmp(line, "C ", 2) == 0)
		return (parse_color(line, walls->ceiling), 1);
	return (0);
}