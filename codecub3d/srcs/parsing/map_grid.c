/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_grid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcastrat <mcastrat@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 16:23:47 by mcastrat          #+#    #+#             */
/*   Updated: 2025/12/25 18:05:34 by mcastrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	get_map_dimensions(char **lines, int start, t_grid *grid)
{
	int	i;
	int	j;
	int	width;
	int	height;

	i = start;
	width = 0;
	height = 0;
	while (lines[i] && is_map_line(lines[i]))
	{
		j = ft_strlen(lines[i]);
		if (lines[i][j - 1] == '\n')
			j--;
		if (j > width)
			width = j;
		height++;
		i++;
	}
	if (height == 0)
		return (printf("Error\nNo map found\n"),0);
	grid->width = width;
	grid->height = height;
	return (1);
}

static int	allocate_map_grid(t_grid *grid)
{
	int	i;

	grid->grid = malloc(sizeof(char *) * (grid->height + 1));
	if (!grid->grid)
		return (0);
	i = 0;
	while (i < grid->height)
	{
		grid->grid[i] = malloc(sizeof(char) * (grid->width + 1));
		if (!grid->grid[i])
			return (0);
		i++;
	}
	grid->grid[i] = NULL;
	return (1);
}

static void	handle_player_position(t_grid *grid, char c, int x, int y)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (grid->player_x != -1)
		{
			printf("Error\nMultiple player positions\n");
			exit(EXIT_FAILURE);
		}
		grid->player_x = x;
		grid->player_y = y;
		grid->player_dir = c;
		grid->grid[y][x] = '0';
	}
	else
		grid->grid[y][x] = c;
}

static void	fill_map_row(t_grid *grid, char *line, int y)
{
	int	x;

	x = 0;
	while (line[x] && line[x] != '\n')
	{
		handle_player_position(grid, line[x], x, y);
		x++;
	}
	while (x < grid->width)
	{
		grid->grid[y][x] = ' ';
		x++;
	}
	grid->grid[y][x] = '\0';
}

int	parse_map_grid(char **lines, int start, t_grid *grid)
{
	int	i;

	grid->player_x = -1;
	grid->player_y = -1;
	if (!get_map_dimensions(lines, start, grid))
		return (0);
	if (!allocate_map_grid(grid))
		return (0);
	i = 0;
	while (i < grid->height)
	{
		fill_map_row(grid, lines[start + i], i);
		i++;
	}
	if (grid->player_x == -1)
		return (printf("Error\nNo player position found\n"), 0);
	return (1);
}
