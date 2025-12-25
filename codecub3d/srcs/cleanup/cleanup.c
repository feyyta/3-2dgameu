/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcastrat <mcastrat@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 17:29:14 by mcastrat          #+#    #+#             */
/*   Updated: 2025/12/25 16:18:47 by mcastrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	free_texture_images(t_data *data)
{
	if (data->tex_north.img)
		mlx_destroy_image(data->mlx, data->tex_north.img);
	if (data->tex_south.img)
		mlx_destroy_image(data->mlx, data->tex_south.img);
	if (data->tex_west.img)
		mlx_destroy_image(data->mlx, data->tex_west.img);
	if (data->tex_east.img)
		mlx_destroy_image(data->mlx, data->tex_east.img);
}

static void	free_texture_paths(t_walls *walls)
{
	if (!walls)
		return ;
	if (walls->north)
	{
		free(walls->north);
		walls->north = NULL;
	}
	if (walls->south)
	{
		free(walls->south);
		walls->south = NULL;
	}
	if (walls->west)
	{
		free(walls->west);
		walls->west = NULL;
	}
	if (walls->east)
	{
		free(walls->east);
		walls->east = NULL;
	}
}

static void	free_map_grid_array(t_grid *grid)
{
	int	i;

	if (!grid || !grid->grid)
		return ;
	i = 0;
	while (i < grid->height)
	{
		if (grid->grid[i])
			free(grid->grid[i]);
		i++;
	}
	free(grid->grid);
	grid->grid = NULL;
}

void	cleanup_game(t_data *data, t_grid *grid, t_walls *walls)
{
	if (!data)
		return ;
	if (data->img)
		mlx_destroy_image(data->mlx, data->img);
	free_texture_images(data);
	free_map_grid_array(grid);
	free_texture_paths(walls);
	if (data->win && data->mlx)
		mlx_destroy_window(data->mlx, data->win);
}

void	cleanup_and_exit(t_data *data, t_grid *grid,
						t_walls *walls, int exit_code)
{
	cleanup_game(data, grid, walls);
	exit(exit_code);
}
