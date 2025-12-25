/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcastrat <mcastrat@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 09:17:42 by mcastrat          #+#    #+#             */
/*   Updated: 2025/12/25 19:01:19 by mcastrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	find_map_start(char **lines, int line_count, t_walls *walls)
{
	int	i;

	i = 0;
	while (i < line_count)
	{
		if (lines[i][0] != '\n' && !parse_config_line(lines[i], walls))
		{
			if (is_map_line(lines[i]))
				return (i);
			else if (lines[i][0] != '\n')
				return (printf("Error\nInvalid line: %s", lines[i]), -1);
		}
		i++;
	}
	return (-1);
}

int	check_map(int argc, char **argv, t_walls *walls, t_grid *grid)//leaaaaaaaaaaaaaaaak
{
	char	**lines;
	int		line_count;
	int		map_start;

	(void)argc;
	init_textures(walls);
	lines = store_map_lines(argv[1], &line_count);
	if (!lines)
		return (0);
	map_start = find_map_start(lines, line_count, walls);
	if (!validate_textures(walls) || map_start == -1
		|| !parse_map_grid(lines, map_start, grid)
		|| !validate_map_closed(grid))
	{
		free_map_lines(lines, line_count);
		return (0);
	}
	return (free_map_lines(lines, line_count), 1);
}