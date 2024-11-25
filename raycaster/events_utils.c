/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 21:19:41 by yboumlak          #+#    #+#             */
/*   Updated: 2024/11/23 21:21:45 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include "raycaster.h"

int	is_collision(t_game *game, t_pos next_pos)
{
	int	x;
	int	y;
	int	end_x;
	int	end_y;

	x = (int)round(next_pos.x - PLAYER_SIZE / 2);
	end_x = (int)round(next_pos.x + PLAYER_SIZE / 2);
	while (x <= end_x)
	{
		y = (int)round(next_pos.y - PLAYER_SIZE / 2);
		end_y = (int)round(next_pos.y + PLAYER_SIZE / 2);
		while (y <= end_y)
		{
			if (game->map.grid[y / TILE_SIZE][x / TILE_SIZE] == '1')
				return (1);
			y++;
		}
		x++;
	}
	return (0);
}

t_pos	calculate_next_position(t_game *game, t_pos current_pos)
{
	t_pos	next_pos;

	next_pos = current_pos;
	if (mlx_is_key_down(game->win.mlx, MLX_KEY_W))
	{
		next_pos.x += PLAYER_SPEED * cos(game->player.angle);
		next_pos.y += PLAYER_SPEED * sin(game->player.angle);
	}
	if (mlx_is_key_down(game->win.mlx, MLX_KEY_S))
	{
		next_pos.x -= PLAYER_SPEED * cos(game->player.angle);
		next_pos.y -= PLAYER_SPEED * sin(game->player.angle);
	}
	if (mlx_is_key_down(game->win.mlx, MLX_KEY_A))
	{
		next_pos.x += PLAYER_SPEED * sin(game->player.angle);
		next_pos.y -= PLAYER_SPEED * cos(game->player.angle);
	}
	if (mlx_is_key_down(game->win.mlx, MLX_KEY_D))
	{
		next_pos.x -= PLAYER_SPEED * sin(game->player.angle);
		next_pos.y += PLAYER_SPEED * cos(game->player.angle);
	}
	return (next_pos);
}
