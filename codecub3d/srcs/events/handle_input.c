/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcastrat <mcastrat@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 13:42:19 by mcastrat          #+#    #+#             */
/*   Updated: 2025/12/25 18:04:02 by mcastrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	close_window(t_data *data)
{
	cleanup_game(data, data->grid, data->walls);
	exit(0);
	return (0);
}

static int	is_valid_position(t_grid *grid, int x, int y)
{
	if (grid->grid[y][x] == '1')
		return (0);
	return (1);
}

static void	move_forward_backward(t_cam *cam, t_grid *grid, int forward)
{
	double	new_x;
	double	new_y;

	if (forward)
	{
		new_x = cam->pos_x + cam->dir_x * MOVE_SPEED;
		new_y = cam->pos_y + cam->dir_y * MOVE_SPEED;
	}
	else
	{
		new_x = cam->pos_x - cam->dir_x * MOVE_SPEED;
		new_y = cam->pos_y - cam->dir_y * MOVE_SPEED;
	}
	if (is_valid_position(grid, (int)new_x, (int)new_y))
	{
		cam->pos_x = new_x;
		cam->pos_y = new_y;
	}
}

static void	move_left_right(t_cam *cam, t_grid *grid, int right)
{
	double	new_x;
	double	new_y;

	if (right)
	{
		new_x = cam->pos_x + cam->plane_x * MOVE_SPEED;
		new_y = cam->pos_y + cam->plane_y * MOVE_SPEED;
	}
	else
	{
		new_x = cam->pos_x - cam->plane_x * MOVE_SPEED;
		new_y = cam->pos_y - cam->plane_y * MOVE_SPEED;
	}
	if (is_valid_position(grid, (int)new_x, (int)new_y))
	{
		cam->pos_x = new_x;
		cam->pos_y = new_y;
	}
}

static void	rotate_camera(t_cam *cam, int right)
{
	double	old_dir_x;
	double	old_plane_x;
	double	rot_speed;

	rot_speed = ROT_SPEED;
	if (!right)
		rot_speed = -rot_speed;
	old_dir_x = cam->dir_x;
	cam->dir_x = cam->dir_x * cos(rot_speed)
		- cam->dir_y * sin(rot_speed);
	cam->dir_y = old_dir_x * sin(rot_speed)
		+ cam->dir_y * cos(rot_speed);
	old_plane_x = cam->plane_x;
	cam->plane_x = cam->plane_x * cos(rot_speed)
		- cam->plane_y * sin(rot_speed);
	cam->plane_y = old_plane_x * sin(rot_speed)
		+ cam->plane_y * cos(rot_speed);
}

int	handle_keypress(int keycode, t_data *data)
{
	if (keycode == KEY_ESC)
		close_window(data);
	else if (keycode == KEY_W)
		move_forward_backward(&data->cam, data->grid, 1);
	else if (keycode == KEY_S)
		move_forward_backward(&data->cam, data->grid, 0);
	else if (keycode == KEY_A)
		move_left_right(&data->cam, data->grid, 0);
	else if (keycode == KEY_D)
		move_left_right(&data->cam, data->grid, 1);
	else if (keycode == KEY_LEFT)
		rotate_camera(&data->cam, 0);
	else if (keycode == KEY_RIGHT)
		rotate_camera(&data->cam, 1);
	return (0);
}
