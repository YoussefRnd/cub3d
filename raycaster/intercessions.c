/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intercessions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:11:21 by yboumlak          #+#    #+#             */
/*   Updated: 2024/10/17 17:28:21 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include "raycaster.h"

void	first_hor_inter(t_game *game)
{
	if (game->ray.is_facing_up)
		game->ray.hor_inter.y = floor(game->player.pos_in_pix.y / TILE_SIZE)
			* TILE_SIZE - 1;
	else if (game->ray.is_facing_down)
		game->ray.hor_inter.y = floor(game->player.pos_in_pix.y / TILE_SIZE)
			* TILE_SIZE + TILE_SIZE;
	game->ray.hor_inter.x = (game->ray.hor_inter.y - game->player.pos_in_pix.y)
		/ tan(game->ray.angle) + game->player.pos_in_pix.x;
}

void	first_ver_inter(t_game *game)
{
	if (game->ray.is_facing_right)
		game->ray.ver_inter.x = floor(game->player.pos_in_pix.x / TILE_SIZE)
			* TILE_SIZE + TILE_SIZE;
	else if (game->ray.is_facing_left)
		game->ray.ver_inter.x = floor(game->player.pos_in_pix.x / TILE_SIZE)
			* TILE_SIZE - 1;
	game->ray.ver_inter.y = game->player.pos_in_pix.y
		+ (game->ray.ver_inter.x - game->player.pos_in_pix.x)
		* tan(game->ray.angle);
}
