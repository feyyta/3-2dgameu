/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcastrat <mcastrat@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 14:22:53 by mcastrat          #+#    #+#             */
/*   Updated: 2025/12/24 10:17:44 by mcastrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* Fonction principale de rendu - Lance le raycasting et dessine l'image
Boucle sur chaque colonne de l'écran (x = 0 à WIN_WIDTH-1) :
1. Lance un rayon pour la colonne x
2. Calcule la distance au mur et la hauteur du mur
3. Dessine plafond + mur + sol pour cette colonne */
void	render_frame(t_data *data, t_walls *walls, t_grid *grid)
{
	t_cast	cast;
	int		x;

	x = 0;
	while (x < WIN_WIDTH)
	{
		prepare_ray(&cast, &data->cam, x);
		setup_step(&cast, &data->cam);
		algo_dda(&cast, grid);
		calculate_wall_distance(&cast, &data->cam);
		draw_column(data, &cast, walls, x);
		x++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}

/* Fonction appelée à chaque frame par mlx_loop_hook
Re-rend l'image à chaque fois (pour voir les mouvements) */
int	render_hook(t_data *data)
{
	render_frame(data, data->walls, data->grid);
	return (0);
}
