/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcastrat <mcastrat@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 13:19:26 by mcastrat          #+#    #+#             */
/*   Updated: 2025/12/22 16:31:48 by mcastrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// Les formules viennet de l'algo DDA (utilsie dans Wolfenstein3d)
void	prepare_ray(t_cast *cast, t_cam *cam, int x) // pour x, calculer dans quelle direction part le rayon
{
	double	camera_x; // coefficient entre -1 et +1 qui dit "où on est sur l'écran" pour calculer la direction du rayon correspondant

	camera_x = 2 * x / (double)WIN_WIDTH - 1;
	cast->dir_x = cam->dir_x + cam->plane_x * camera_x;
	cast->dir_y = cam->dir_y + cam->plane_y * camera_x;
	cast->map_x = (int)cam->pos_x;
	cast->map_y = (int)cam->pos_y;
	cast->delta_x = fabs(1 / cast->dir_x); // fabs() = valeur absolue pour les nombres à virgule
	cast->delta_y = fabs(1 / cast->dir_y); // le  1 / ray_dir c'est pour calculer combien de distance le rayon doit parcourir pour traverser une case complète. Plus la direction est grande, moins il faut de distance.
}

void	setup_step(t_cast *cast, t_cam *cam) // Calculer comment avancer et quelle est la première bordure
{
	if (cast->dir_x < 0)
	{
		cast->step_x = -1; // va-t-on à gauche/droite ? haut/bas ?
		cast->side_x = (cam->pos_x - cast->map_x) * cast->delta_x; // distance jusqu'au premier bord
	}
	else
	{
		cast->step_x = 1;
		cast->side_x = (cast->map_x + 1.0 - cam->pos_x)
			* cast->delta_x;
	}
	if (cast->dir_y < 0)
	{
		cast->step_y = -1;
		cast->side_y = (cam->pos_y - cast->map_y) * cast->delta_y;
	}
	else
	{
		cast->step_y = 1;
		cast->side_y = (cast->map_y + 1.0 - cam->pos_y)
			* cast->delta_y;
	}
}


void	algo_dda(t_cast *cast, t_grid *grid)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (cast->side_x < cast->side_y)
		{
			cast->side_x += cast->delta_x;
			cast->map_x += cast->step_x;
			cast->side = 0;
		}
		else
		{
			cast->side_y += cast->delta_y;
			cast->map_y += cast->step_y;
			cast->side = 1;
		}
		if (grid->grid[cast->map_y][cast->map_x] == '1')
			hit = 1;
	}
}

void	calculate_wall_distance(t_cast *cast, t_cam *cam)
{
	if (cast->side == 0)
		cast->distance = (cast->map_x - cam->pos_x
				+ (1 - cast->step_x) / 2) / cast->dir_x;
	else
		cast->distance = (cast->map_y - cam->pos_y
				+ (1 - cast->step_y) / 2) / cast->dir_y;
	cast->wall_h = (int)(WIN_HEIGHT / cast->distance);
	if (cast->side == 0)
		cast->wall_x = cam->pos_y + cast->distance * cast->dir_y;
	else
		cast->wall_x = cam->pos_x + cast->distance * cast->dir_x;
	cast->wall_x -= floor(cast->wall_x);
}
