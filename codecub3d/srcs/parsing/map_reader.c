/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcastrat <mcastrat@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 11:34:18 by mcastrat          #+#    #+#             */
/*   Updated: 2025/12/25 19:07:25 by mcastrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
//leaaaaaaaaaaaaaaaaaaaaaakkkkkkkkkkk
static int	count_file_lines(int fd)
{
	char	*current_line;
	int		total;

	total = 0;
	current_line = get_next_line(fd);
	while (current_line)
	{
		total++;
		free(current_line);
		current_line = get_next_line(fd);
	}
	return (total);
}

static char	**fill_lines_array(int fd, int total_lines)//leak
{
	char	**lines_array;
	int		index;

	lines_array = malloc(sizeof(char *) * (total_lines + 1));
	if (!lines_array)
		return (printf("succed\n"), NULL);
	index = 0;
	while (index < total_lines)
	{
		lines_array[index] = get_next_line(fd);
		if (!lines_array[index])
			return (free_map_lines(lines_array, index), NULL);
		index++;
	}
	lines_array[index] = NULL;
	return (lines_array);
}

char	**store_map_lines(char *filename, int *line_count)
{
	char	**result;
	int		total_lines;
	int		fd_first;
	int		fd_second;

	// 1ere ouverture pour compter tte les lignes
	fd_first = open(filename, O_RDONLY);
	if (fd_first == -1)
		return (NULL);
	total_lines = count_file_lines(fd_first);
	close(fd_first);
	if (total_lines <= 0)
		return (NULL);
	// 2eme ouverture pour aller la taille exacte et remplir avec fill_lines_array
	fd_second = open(filename, O_RDONLY);
	if (fd_second == -1)
		return (NULL);
	result = fill_lines_array(fd_second, total_lines);
	close(fd_second);
	*line_count = total_lines;
	return (result);
}

void	free_map_lines(char **lines, int line_count)
{
	int	i;

	i = 0;
	while (i < line_count)
	{
		free(lines[i]);
		i++;
	}
	free(lines);
}

void	free_map_grid(t_grid *grid)
{
	int	i;

	i = 0;
	while (grid->grid && grid->grid[i])
	{
		free(grid->grid[i]);
		i++;
	}
	if (grid->grid)
		free(grid->grid);
}