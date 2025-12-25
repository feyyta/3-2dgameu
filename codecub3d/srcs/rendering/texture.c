/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcastrat <mcastrat@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 09:47:13 by mcastrat          #+#    #+#             */
/*   Updated: 2025/12/20 13:54:26 by mcastrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* Sélectionne quelle texture utiliser selon l'orientation du mur */
static t_img	*select_texture(t_data *data, t_cast *cast)
{
	if (cast->side == 0)
	{
		if (cast->step_x > 0)
			return (&data->tex_east);
		else
			return (&data->tex_west);
	}
	else
	{
		if (cast->step_y > 0)
			return (&data->tex_south);
		else
			return (&data->tex_north);
	}
}

/* Dessine un mur texturé pixel par pixel
Pour chaque pixel Y du mur :
1. Calcule quelle ligne de la texture (tex_y) correspond
2. Récupère la couleur du pixel (tex_x, tex_y) de la texture
3. Affiche ce pixel à l'écran */
void	draw_wall_tex(t_data *data, t_cast *cast, int x, int start, int end)
{
	t_img	*tex;
	int				tex_x;
	int				tex_y;
	int				y;
	double			step;
	double			tex_pos;

	tex = select_texture(data, cast);
	tex_x = (int)(cast->wall_x * (double)tex->width);
	if ((cast->side == 0 && cast->step_x < 0)
		|| (cast->side == 1 && cast->step_y > 0))
		tex_x = tex->width - tex_x - 1;
	step = 1.0 * tex->height / cast->wall_h;
	tex_pos = (start - WIN_HEIGHT / 2 + cast->wall_h / 2) * step;
	y = start;
	while (y <= end)
	{
		tex_y = (int)tex_pos & (tex->height - 1);
		tex_pos += step;
		set_pixel(data, x, y, get_tex_color(tex, tex_x, tex_y));
		y++;
	}
}
