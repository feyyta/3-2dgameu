/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcastrat <mcastrat@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 10:14:37 by mcastrat          #+#    #+#             */
/*   Updated: 2025/12/23 08:42:15 by mcastrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	set_direction_north(t_cam *cam)
{
	cam->dir_x = 0;
	cam->dir_y = -1;
	cam->plane_x = FOV;
	cam->plane_y = 0;
}

static void	set_direction_south(t_cam *cam)
{
	cam->dir_x = 0;
	cam->dir_y = 1;
	cam->plane_x = -FOV;
	cam->plane_y = 0;
}

static void	set_direction_east(t_cam *cam)
{
	cam->dir_x = 1;
	cam->dir_y = 0;
	cam->plane_x = 0;
	cam->plane_y = FOV;
}

static void	set_direction_west(t_cam *cam)
{
	cam->dir_x = -1;
	cam->dir_y = 0;
	cam->plane_x = 0;
	cam->plane_y = -FOV;
}

void	init_player(t_cam *cam, t_grid *grid)
{
	cam->pos_x = (double)grid->player_x + 0.5; // Le +0.5 centre le joueur au milieu de la case au lieu du coin
	cam->pos_y = (double)grid->player_y + 0.5;
	if (grid->player_dir == 'N')
		set_direction_north(cam);
	else if (grid->player_dir == 'S')
		set_direction_south(cam);
	else if (grid->player_dir == 'E')
		set_direction_east(cam);
	else if (grid->player_dir == 'W')
		set_direction_west(cam);
}
