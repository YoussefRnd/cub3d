/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrahimi <hbrahimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 04:48:05 by hbrahimi          #+#    #+#             */
/*   Updated: 2024/11/04 17:04:17 by hbrahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

double	get_y_in_texture(t_game *game, double wall_hit)
{
	double	y;

	y = wall_hit / game->wall.height * game->components->east_texture->height;
	return (y);
}

double	get_x_in_texture(t_game *game)
{
	double	x;

	if (game->ray.was_hit_vertical)
		x = (game->ray.wall_hit.y / TILE_SIZE - floor(game->ray.wall_hit.y
					/ TILE_SIZE)) * game->components->east_texture->width;
	else
		x = (game->ray.wall_hit.x / TILE_SIZE - floor(game->ray.wall_hit.x
					/ TILE_SIZE)) * game->components->east_texture->width;
	return (x);
}
// int	get_pixel_from_buffer(t_game *game, double x ,double y)
// {

// 	uint8_t *pixels = game->components->east_texture->pixels;
// 	int index = (y * game->components->east_texture->width
// 			* game->components->east_texture->bytes_per_pixel) + x
// 		* game->components->east_texture->bytes_per_pixel;
// 	uint8_t *rgba = &pixels[index];
// 	return ((rgba[0] << 24) | (rgba[1] << 16) | (rgba[2] << 8) | rgba[3]);
// }

int get_pixel_from_buffer(t_game *game, double x, double y)
{
	uint8_t *pixels = game->components->east_texture->pixels;
	int texture_width = game->components->east_texture->width;
	int bytes_per_pixel = game->components->east_texture->bytes_per_pixel;

	// Cast x and y to integers
	int x_int = (int)x;
	int y_int = (int)y;

	// Ensure x and y are within the texture bounds
	// if (x_int < 0 || x_int >= texture_width || y_int < 0 || y_int >= game->components->east_texture->height)
	// {
	// 	return 0; // Return a default color or handle error
	// }

	// Calculate the index
	int index = (y_int * texture_width + x_int) * bytes_per_pixel;
	uint8_t *rgba = &pixels[index];

	// Combine RGBA components into a single integer
	return ((rgba[0] << 24) | (rgba[1] << 16) | (rgba[2] << 8) | rgba[3]);
}

int	get_texture_color(t_game *game, double y_in_wall)
{
	double	x_in_texture;
	double	y_in_texture;

	x_in_texture = get_x_in_texture(game);
	y_in_texture = get_y_in_texture(game, y_in_wall);
	return (get_pixel_from_buffer(game, x_in_texture, y_in_texture));
}
