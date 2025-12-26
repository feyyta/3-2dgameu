/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcastrat <mcastrat@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 08:53:41 by mcastrat          #+#    #+#             */
/*   Updated: 2025/12/26 15:36:41 by mcastrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int main(int argc, char **argv)
{
    t_data      data;
    t_walls     walls;
    t_grid       grid;

    ft_bzero(&data, sizeof(t_data));
    ft_bzero(&walls, sizeof(t_walls));
    ft_bzero(&grid, sizeof(t_grid));
    if (check_args(argc, argv) == 0)
        cleanup_and_exit(&data, &grid, &walls, EXIT_FAILURE);
    if (check_map(argc, argv, &walls, &grid) == 0)
        cleanup_and_exit(&data, &grid, &walls, EXIT_FAILURE);
    data.mlx = mlx_init();
    if (!data.mlx)
    {
        printf("Error\nFailed to initialize MLX\n");
        cleanup_and_exit(&data, &grid, &walls, 1);
    }
    init_wall_textures(&data, &walls);
    init_player(&data.cam, &grid);
    data.grid = &grid;
    data.walls = &walls;
    ///neeed split to mlx ft folder need to make it
    data.win = mlx_new_window(data.mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
    if (!data.win)
    {
        printf("Error\nFailed to create window\n");
        cleanup_and_exit(&data, &grid, &walls, 1);
    }
    data.img = mlx_new_image(data.mlx, WIN_WIDTH, WIN_HEIGHT);
    if (!data.img)
    {
        printf("Error\nFailed to create image\n");
        cleanup_and_exit(&data, &grid, &walls, 1);
    }
    data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel,
            &data.line_length, &data.endian);
    mlx_hook(data.win, 17, 1L<<17, close_window, &data);
    mlx_hook(data.win, 2, 1L<<0, handle_keypress, &data);
    mlx_loop_hook(data.mlx, render_hook, &data);
    mlx_loop(data.mlx);
    cleanup_game(&data, &grid, &walls);
    return (0);
}
