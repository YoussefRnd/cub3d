/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrahimi <hbrahimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 04:48:05 by hbrahimi          #+#    #+#             */
/*   Updated: 2024/11/04 21:57:23 by hbrahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

double	get_y_in_texture(t_game *game, double wall_hit, mlx_texture_t *texture)
{
	double	y;

	y = wall_hit / game->wall.height * texture->height;
	return (y);
}

double	get_x_in_texture(t_game *game,mlx_texture_t *texture)
{
	double	x;

	if (game->ray.was_hit_vertical)
		x = (game->ray.wall_hit.y / TILE_SIZE - floor(game->ray.wall_hit.y
					/ TILE_SIZE)) * texture->width;
	else
		x = (game->ray.wall_hit.x / TILE_SIZE - floor(game->ray.wall_hit.x
					/ TILE_SIZE)) * texture->width;
	return (x);
}

int	get_pixel_from_buffer(double x, double y, mlx_texture_t *texture)
{
	uint8_t	*pixels;
	int		texture_width;
	int		bytes_per_pixel;
	int		x_int;
	int		y_int;
	int		index;
	uint8_t	*rgba;

	pixels = texture->pixels;
	texture_width = texture->width;
	bytes_per_pixel = texture->bytes_per_pixel;
	x_int = (int)x;
	y_int = (int)y;
	index = (y_int * texture_width + x_int) * bytes_per_pixel;
	rgba = &pixels[index];
	return ((rgba[0] << 24) | (rgba[1] << 16) | (rgba[2] << 8) | rgba[3]);
}

void	get_the_right_texture(t_game *game, mlx_texture_t **texture)
{
	if (!game->ray.was_hit_vertical)
	{	
		if (game->ray.is_facing_up)
			*texture = game->components->north_texture;
		else if (game->ray.is_facing_down)
			*texture = game->components->south_texture;
	}
	else
	{
		if (game->ray.is_facing_left)
			*texture = game->components->west_texture;
		else if (game->ray.is_facing_right)
			*texture = game->components->east_texture;	
	}
}


int	get_texture_color(t_game *game, double y_in_wall)
{
	double	x_in_texture;
	double	y_in_texture;
	mlx_texture_t	*texture;

	get_the_right_texture(game, &texture);
	x_in_texture = get_x_in_texture(game, texture);
	y_in_texture = get_y_in_texture(game, y_in_wall, texture);
	return (get_pixel_from_buffer(x_in_texture, y_in_texture, texture));
}
