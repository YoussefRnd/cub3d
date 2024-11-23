/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intercessions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:11:21 by yboumlak          #+#    #+#             */
/*   Updated: 2024/11/23 21:24:22 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include "raycaster.h"

void	first_hor_inter(t_game *game)
{
	if (game->ray.is_facing_up)
		game->ray.hor_inter.y = floor(game->player.pos_in_pix.y / TILE_SIZE)
			* TILE_SIZE - 0.00000000001;
	else if (game->ray.is_facing_down)
		game->ray.hor_inter.y = floor(game->player.pos_in_pix.y / TILE_SIZE)
			* TILE_SIZE + TILE_SIZE;
	game->ray.hor_inter.x = (game->ray.hor_inter.y - game->player.pos_in_pix.y)
		/ tan(game->ray.angle) + game->player.pos_in_pix.x;
}

void	other_hor_inter(t_game *game)
{
	double	xa;
	double	ya;

	if (game->ray.is_facing_down)
		ya = TILE_SIZE;
	else
		ya = -TILE_SIZE;
	xa = ya / tan(game->ray.angle);
	while (game->ray.hor_inter.x >= 0
		&& game->ray.hor_inter.x < game->map.size.x * TILE_SIZE
		&& game->ray.hor_inter.y >= 0
		&& game->ray.hor_inter.y < game->map.size.y * TILE_SIZE)
	{
		if (game->map.grid[(int)(game->ray.hor_inter.y
				/ TILE_SIZE)][(int)(game->ray.hor_inter.x / TILE_SIZE)] == '1')
		{
			game->ray.found_hor_wall_hit = true;
			break ;
		}
		else
		{
			game->ray.hor_inter.x += xa;
			game->ray.hor_inter.y += ya;
		}
	}
}

void	first_ver_inter(t_game *game)
{
	if (game->ray.is_facing_right)
		game->ray.ver_inter.x = floor(game->player.pos_in_pix.x / TILE_SIZE)
			* TILE_SIZE + TILE_SIZE;
	else if (game->ray.is_facing_left)
		game->ray.ver_inter.x = floor(game->player.pos_in_pix.x / TILE_SIZE)
			* TILE_SIZE - 0.00000000001;
	game->ray.ver_inter.y = game->player.pos_in_pix.y + (game->ray.ver_inter.x
			- game->player.pos_in_pix.x) * tan(game->ray.angle);
}

void	other_ver_inter(t_game *game)
{
	double	xb;
	double	yb;

	if (game->ray.is_facing_right)
		xb = TILE_SIZE;
	else
		xb = -TILE_SIZE;
	yb = xb * tan(game->ray.angle);
	while (game->ray.ver_inter.x >= 0
		&& game->ray.ver_inter.x < game->map.size.x * TILE_SIZE
		&& game->ray.ver_inter.y >= 0
		&& game->ray.ver_inter.y < game->map.size.y * TILE_SIZE)
	{
		if (game->map.grid[(int)(game->ray.ver_inter.y
				/ TILE_SIZE)][(int)(game->ray.ver_inter.x / TILE_SIZE)] == '1')
		{
			game->ray.found_ver_wall_hit = true;
			break ;
		}
		else
		{
			game->ray.ver_inter.x += xb;
			game->ray.ver_inter.y += yb;
		}
	}
}
