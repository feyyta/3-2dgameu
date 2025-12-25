/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcastrat <mcastrat@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 11:28:51 by mcastrat          #+#    #+#             */
/*   Updated: 2025/12/24 15:39:22 by mcastrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* Convertit RGB (tableau de 3 ints) en un seul int couleur
Format : 0x00RRGGBB (hexadécimal)
Exemple : R=220, G=100, B=111 → 0x00DC646F */
int	rgb_to_color(int *rgb)
{
	return ((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]);
}

/* Récupère la couleur d'un pixel (tex_x, tex_y) depuis une texture
Même principe que set_pixel mais en lecture au lieu d'écriture */
int	get_tex_color(t_img *tex, int tex_x, int tex_y)
{
	char	*pixel;

	pixel = tex->addr + (tex_y * tex->line_length + tex_x
			* (tex->bits_per_pixel / 8));
	return (*(unsigned int *)pixel);
}

void	set_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel
				/ 8));
	*(unsigned int *)dst = color;
}

/* Dessine une ligne verticale de 'start_y' à 'end_y' pour la colonne 'x'
Utilisé pour dessiner un segment de mur à l'écran */
void	draw_vline(t_data *data, int x, int start_y, int end_y,
		int color)
{
	int	y;

	y = start_y;
	while (y <= end_y)
	{
		set_pixel(data, x, y, color);
		y++;
	}
}

/* Calcule où commence et finit le mur sur l'écran
start = où commence le mur (haut de l'écran = 0)
end = où finit le mur (bas de l'écran = WIN_HEIGHT) */
void	calculate_draw_limits(t_cast *cast, int *start, int *end)
{
	*start = -cast->wall_h / 2 + WIN_HEIGHT / 2;
	if (*start < 0)
		*start = 0;
	*end = cast->wall_h / 2 + WIN_HEIGHT / 2;
	if (*end >= WIN_HEIGHT)
		*end = WIN_HEIGHT - 1;
}

/* Dessine une colonne complète : plafond, mur texturé, sol
Pour chaque colonne X de l'écran (0 à 799), on dessine du haut en bas */
void	draw_column(t_data *data, t_cast *cast, t_walls *walls, int x)
{
	int	start;
	int	end;

	calculate_draw_limits(cast, &start, &end);
	draw_vline(data, x, 0, start - 1, rgb_to_color(walls->ceiling));
	draw_wall_tex(data, cast, x, start, end);
	draw_vline(data, x, end + 1, WIN_HEIGHT - 1,
		rgb_to_color(walls->floor));
}
