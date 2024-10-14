/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:11:21 by yboumlak          #+#    #+#             */
/*   Updated: 2024/10/14 17:33:42 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include "raycaster.h"

void	first_hor_inter(t_game *game)
{
	if (game->ray.ray_facing == 'N')
		game->ray.hor_inter.y = floor(game->player.pos.x / TILE_SIZE)
			* TILE_SIZE - 1;
	else if (game->ray.ray_facing == 'S')
		game->ray.hor_inter.y = floor(game->player.pos.x / TILE_SIZE)
			* TILE_SIZE + TILE_SIZE;
	game->ray.hor_inter.x = (game->ray.hor_inter.y - game->player.pos.y)
		/ tan(game->ray.angle) + game->player.pos.x;
}

void	other_hor_inter(t_game *game)
{
	if (game->ray.ray_facing == 'N')
		game->ray.hor_inter.y -= TILE_SIZE;
	else if (game->ray.ray_facing == 'S')
		game->ray.hor_inter.y += TILE_SIZE;
	game->ray.hor_inter.x = TILE_SIZE / tan(game->ray.angle);
}

void	first_ver_inter(t_game *game)
{
	if (game->ray.ray_facing == 'E')
		game->ray.ver_inter.x = floor(game->player.pos.y / TILE_SIZE)
			* TILE_SIZE + TILE_SIZE;
	else if (game->ray.ray_facing == 'W')
		game->ray.ver_inter.x = floor(game->player.pos.y / TILE_SIZE)
			* TILE_SIZE - 1;
	game->ray.ver_inter.y = game->player.pos.y + (game->player.pos.x
			- game->ray.ver_inter.x) * tan(game->ray.angle);
}

void	other_ver_inter(t_game *game)
{
	if (game->ray.ray_facing == 'E')
		game->ray.ver_inter.x += TILE_SIZE;
	else if (game->ray.ray_facing == 'W')
		game->ray.ver_inter.x -= TILE_SIZE;
	game->ray.ver_inter.y += game->ray.ver_inter.x * tan(game->ray.angle);
}