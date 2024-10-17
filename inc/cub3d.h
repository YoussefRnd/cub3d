/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 13:24:56 by yboumlak          #+#    #+#             */
/*   Updated: 2024/10/15 12:33:33 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../lib/Libft/libft.h"
# include "../lib/MLX42/include/MLX42/MLX42.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define TILE_SIZE 32
# define TILE_MARGIN 1
# define PLAYER_SIZE 7
# define PLAYER_SPEED 3
# define FOV 60
# define WIDTH 800
# define HEIGHT 600

# define WALL_COLOR 0xFF0000FF
# define FLOOR_COLOR 0xFFFFFFFF

typedef struct s_pos
{
	double		x;
	double		y;
}				t_pos;

typedef struct s_player
{
	t_pos		pos;
	t_pos		pos_in_pix;
	char		orientation;
	double		angle;
}				t_player;

typedef struct s_map
{
	char		**grid;
	t_pos		size;
}				t_map;

typedef struct s_win
{
	char		*title;
	void		*mlx;
	mlx_image_t	*img;
	mlx_image_t	*mini_map;
}				t_win;

typedef struct s_ray
{
	double		angle;
	int			is_facing_down;
	int			is_facing_right;
	int			is_facing_up;
	int			is_facing_left;
	double		distance;
	t_pos		ver_inter;
	t_pos		hor_inter;
	t_pos		wall_hit;

}				t_ray;
typedef struct s_game
{
	t_player	player;
	t_map		map;
	t_win		win;
	t_ray		ray;
}				t_game;

#endif
