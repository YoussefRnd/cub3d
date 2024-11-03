/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrahimi <hbrahimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 04:48:05 by hbrahimi          #+#    #+#             */
/*   Updated: 2024/11/03 16:47:57 by hbrahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// void	put_on_textures(t_game *game)
// {
// 	float texture_x;
// 	// float texture_y;
// 	if (!game->ray.was_hit_vertical)
// 		texture_x = ((int)game->ray.hor_inter.x % TILE_SIZE)
// 			* (game->components->east_texture->width / TILE_SIZE);
// 	else
// 		texture_x = (((int)game->ray.ver_inter.y % TILE_SIZE)
// 				* (game->components->north_texture->width / TILE_SIZE));

// }

double	get_y_in_texture(t_game *game)
{
	double	y;

	y = game->ray.wall_hit.y / game->wall.height
		* game->components->east_texture->height;
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
	return x;
}

int	get_texture_color(t_game *game)
{
	double x_in_texture;
	double y_in_texture;

	y_in_texture = get_y_in_texture(game);
	x_in_texture = get_x_in_texture(game);
	// return 1;
	
}