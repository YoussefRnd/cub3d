/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrahimi <hbrahimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 13:24:56 by yboumlak          #+#    #+#             */
/*   Updated: 2024/11/27 06:56:48 by hbrahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../lib/Libft/libft.h"
# include "../lib/MLX42/include/MLX42/MLX42.h"
# include "parsing.h"
# include <fcntl.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>

# define TILE_SIZE 30
# define PLAYER_SIZE 7
# define PLAYER_SPEED 4
# define WIDTH 1920
# define HEIGHT 1080
# define WALL_COLOR 0xFF0000FF
# define FLOOR_COLOR 0xFFFFFFFF
# define PLAYER_COLOR 0x00FF00FF

typedef struct s_player
{
	t_pos			pos;
	t_pos			pos_in_pix;
	char			orientation;
	double			angle;
}					t_player;

typedef struct s_map
{
	char			**grid;
	t_pos			size;
}					t_map;

typedef struct s_win
{
	char			*title;
	void			*mlx;
	mlx_image_t		*img;
}					t_win;

typedef struct s_ray
{
	double			angle;
	int				is_facing_down;
	int				is_facing_right;
	int				is_facing_up;
	int				is_facing_left;
	double			distance;
	t_pos			ver_inter;
	t_pos			hor_inter;
	t_pos			wall_hit;
	int				color;
	int				was_hit_vertical;
	bool			found_hor_wall_hit;
	bool			found_ver_wall_hit;
}					t_ray;

typedef struct s_wall
{
	double			distance;
	double			height;
}					t_wall;
typedef struct s_game
{
	t_player		player;
	t_map			map;
	t_win			win;
	t_ray			ray;
	t_wall			wall;
	t_components	*components;
	int				ceiling_color;
	int				floor_color;
}					t_game;

int					get_texture_color(t_game *game, double y_in_wall);
int					get_length(char *array[]);

#endif
