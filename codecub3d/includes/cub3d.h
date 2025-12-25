/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcastrat <mcastrat@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 09:00:33 by mcastrat          #+#    #+#             */
/*   Updated: 2025/12/25 16:52:17 by mcastrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# include "../libft/inc/libft.h"
# include "../libft/inc/get_next_line.h"

# define WIN_WIDTH 800
# define WIN_HEIGHT 600
# define FOV 0.66

#define KEY_ESC     65307
#define KEY_W       119
#define KEY_A       97
#define KEY_S       115
#define KEY_D       100
#define KEY_LEFT    65361
#define KEY_RIGHT   65363

#define MOVE_SPEED  0.1
#define ROT_SPEED   0.05

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_grid
{
	char	**grid;
	int		width;
	int		height;
	int		player_x;
	int		player_y;
	char	player_dir;
}	t_grid;

typedef struct s_walls
{
	char *north;
	char *south;
	char *west;
	char *east;

	int floor[3];
	int ceiling[3];
}	t_walls;

typedef struct s_cam // position et direction du joueur
{
	double  pos_x;      // Position X dans la map (coordonnees)
    double  pos_y;      // Position Y dans la map
    double  dir_x;      // Vecteur direction X (où regarde le joueur)
    double  dir_y;      // Vecteur direction Y
    double  plane_x;    // Vecteur plan caméra X (pour le FOV)
    double  plane_y;    // Vecteur plan caméra Y
}	t_cam;

typedef struct s_data
{
	void	*mlx;
	void	*win;

	t_img	tex_north;
	t_img	tex_south;
	t_img	tex_west;
	t_img	tex_east;

	t_cam       cam;
	t_grid      *grid;
	t_walls     *walls;

	void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;

}	t_data;

typedef struct s_cast
{
    double  dir_x;
    double  dir_y;

    int     map_x;
    int     map_y;

    double  side_x;
    double  side_y;

    double  delta_x;
    double  delta_y;

    int     step_x;
    int     step_y;

    double  distance;

    int     side;

    int     wall_h;

    double  wall_x;
}   t_cast;

int		check_args(int argc, char **argv);
int		check_map(int argc, char **argv, t_walls *walls, t_grid *grid);

void	parse_color(char *line, int *color_array);
void	parse_textures(char *line, t_walls *walls);
void	init_textures(t_walls *walls);

int		is_map_line(char *line);
int		validate_map_closed(t_grid *grid);
int		validate_textures(t_walls *walls);
int		parse_config_line(char *line, t_walls *walls);

char	**store_map_lines(char *filename, int *line_count);
void	free_map_lines(char **lines, int line_count);
void	free_map_grid(t_grid *grid);

int		parse_map_grid(char **lines, int start, t_grid *grid);

//src/textures
void    init_wall_textures(t_data *data, t_walls *walls);

//src/player
void	init_player(t_cam *cam, t_grid *grid);

//src/raycasting
void    prepare_ray(t_cast *cast, t_cam *cam, int x);
void    setup_step(t_cast *cast, t_cam *cam);
void    algo_dda(t_cast *cast, t_grid *grid);
void    calculate_wall_distance(t_cast *cast, t_cam *cam);

//src/rendering
void    render_frame(t_data *data, t_walls *walls, t_grid *grid);
int     render_hook(t_data *data);
void    set_pixel(t_data *data, int x, int y, int color);
void    draw_vline(t_data *data, int x, int start_y, int end_y,
			int color);
void    calculate_draw_limits(t_cast *cast, int *start, int *end);
void    draw_column(t_data *data, t_cast *cast, t_walls *walls, int x);
int     rgb_to_color(int *rgb);
int     get_tex_color(t_img *tex, int tex_x, int tex_y);
void    draw_wall_tex(t_data *data, t_cast *cast, int x, int start,
			int end);

//src/events
int     handle_keypress(int keycode, t_data *data);
int     close_window(t_data *data);

//src/cleanup
void	cleanup_game(t_data *data, t_grid *grid, t_walls *walls);
void	cleanup_and_exit(t_data *data, t_grid *grid, t_walls *walls,
			int exit_code);

#endif